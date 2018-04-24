/******************************************************************************
 * Module..: SDK -- Software development kit for Leddar products.
 *
 * \file    Main.c
 *
 * \brief   Simple console program demonstrating the use of Leddar Tech's
 *					"read data" function
 * Platform: Win32, Linux
 *
 * Copyright (c) 2013-2015 LeddarTech Inc. All rights reserved.
 * Information contained herein is or may be confidential and proprietary to
 * LeddarTech inc. Prior to using any part of the software development kit
 * accompanying this notice, you must accept and agree to be bound to the
 * terms of the LeddarTech Inc. license agreement accompanying this file.
 *
 ******************************************************************************
 *
 *	DISCLAIMER: This program is a modified form of the LeddarCDemo.
 *
 *  Modified by Austin Scampini, Caleb Kisby
 *  Documentation modified by Caleb Kisby
 *  Date last modified: 8 December 2017
 *
*******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <chrono>

#include "leddarthread.h"

#include <QCoreApplication>
#include <QThread>
#include <QObject>
#include <QFile>
#include <functional>

#define ARRAY_LEN( a )  (sizeof(a)/sizeof(a[0]))



/*********************************************************************
 *********************************************************************
                           PUBLIC
 *********************************************************************
**********************************************************************/



/*********************************************************************
 * The usual constructor.
 *
 * We establish that this thread is running, and has not been stopped.
 * We also register the type 'vector<float>' so that we may emit objects
 * of this type.
 *
 * We also allocate space for a 'LeddarHandle' gHandle for dealing with Leddar
 * file and live streaming.
 *
***/
LeddarStream::LeddarStream() {

    this->gHandle = new LeddarHandle();
    qRegisterMetaType<vector<float> >("vector<float>");
    isstopped = true;
    isrunning = false;

    // Initialize the Leddar Handle.
    this->gHandle = LeddarCreate();

    orientation = HORIZONTAL;

//    LeddarSetProperty( this->gHandle, PID_ACCUMULATION_EXPONENT, 0, 128 );
//    LeddarSetProperty(this->gHandle, PID_OVERSAMPLING_EXPONENT, 0, 4);
}


/*********************************************************************
 * The usual destructor.
***/
LeddarStream::~LeddarStream() {
    // Destroy the handle.
    LeddarDestroy(this->gHandle);

    return;
}


/*********************************************************************
 * Function to read live data from the sensor.
 *
 * We detect the next set of points detected by the sensor, and store
 * them in a 'float' 'vector'.  We then emit these points and their
 * identifying index.  We continue reading points until either there
 * are no more points available, this thread stops running, or this
 * thread is stopped.
***/
void LeddarStream::ReadLiveData( void )
{
cout << "Entering ReadLiveData" << endl;
    int currentRecordIndex;
    vector<float> dataPoints;
    unsigned int i, lCount;
    LdDetection lDetections[16];

    if (!isrunning || isstopped) return;

    CheckError( LeddarStartDataTransfer( this->gHandle, LDDL_DETECTIONS ) );

    while (LeddarWaitForData(this->gHandle, 2000000) == LD_SUCCESS && isrunning && !isstopped) {
        LeddarGetDetections( this->gHandle, lDetections, ARRAY_LEN( lDetections ));
        lCount = LeddarGetDetectionCount( this->gHandle );

        /******************************
         * Run some edge-case tests.
        ***/
        if (lCount == 0) {
            cout << "ERROR: ReadLiveData - NO POINTS DETECTED!" << endl;

            // The official Leddar documentation suggests sending LeddarGetDetections to
            // a callback function.  Otherwise, the documentation suggests that we are
            // "not guranteed to get coherent data."  We could not get the callback working
            // with our Qt object-oriented structure.  Instead, I have determined that the
            // only likely data incoherence involves receiving random 0 vectors of points.
            // We 'continue' in case this is the case, so that we can later get actual data.
            continue;
        }
        if (lCount > ARRAY_LEN(lDetections)) {
            cout << "LeddarStream::ReadLiveData -> ERROR: ReadLiveData - More points detected than expected: " << lCount << endl;
//            continue;
            /***************
             * HOT FIX: At Distances > 10 meter > 16 points are always detected! I just shrink lCount to 16
             */
            lCount = 16;

            // lCount = ARRAY_LEN( lDetections );
            // This was Leddar's default behavior.  I guess they're really bad testers, eh?
        } else if (lCount < ARRAY_LEN(lDetections)) {
            // TODO: What do we do in the situation where we get fewer points than expected?
            // This can happen if the sensor is partially covered, or alternatively if the
            // sensor sees half of a wall.  Right now we 'continue' so that we don't get a
            // major crash.
            cout << "LeddarStream::ReadLiveData -> ERROR: ReadLiveData - Fewer points detected than expected: " << lCount << endl;
            continue;
        } else {
            cout << "ReadLiveData has exactly as many points as expected.";
        }
        /******************************/

        // When replaying a record, display the current index
        if ( LeddarGetRecordSize( this->gHandle ) != 0 )
        {
            currentRecordIndex = LeddarGetCurrentRecordIndex(this->gHandle);
            cout << currentRecordIndex << endl;
        }

        // Output the detected points to the console.
        for (i=0; i < lCount; i++)
        {
            cout << lDetections[i].mDistance << " ";
            dataPoints.push_back(lDetections[i].mDistance);
        }
        cout << endl;

        // Signal the detected points to the GUI.
        emit this->sendDataPoints(currentRecordIndex, dataPoints, orientation);

        dataPoints.erase(dataPoints.begin(), dataPoints.end());
        QCoreApplication::processEvents();
    }
    // Emit all zeros
//    ClearData(lCount);

    LeddarStopDataTransfer( this->gHandle );
    StopStream();
cout << "Exiting ReadLiveData" << endl;
}


/*********************************************************************
 * Function to record data captured by the Leddar into the given file
 *
 * input: fileName - Absolute filepath and name e.g. /home/x/y.ltl
 *
***/
void LeddarStream::RecordLiveData(string fileName)
{
cout << "LeddarStream::RecordLiveData -> Entering RecordLiveData" << endl;

    // Redundant Code
    if ( !isrunning || isstopped) {
        cout << "LeddarStream::RecordLiveData -> Stopping Thread" << endl;
        if ( LeddarGetRecording(this->gHandle) ) {
            LeddarStopRecording(this->gHandle);
        }
        return;
    }

    // Get the index marking the end of the Path to the file
    int last_slash = fileName.find_last_of('/');

    // Get the path and convert to char array
    char file_dir[fileName.length() + 1];
    strcpy(file_dir, fileName.substr(0,last_slash).c_str());

    // Set the save directory.
    LeddarConfigureRecording(file_dir, 0, 0);

    // Leddar recording does not allow us to specify the save file before hand
    LeddarChar temp_file[255];

//    cout << "LeddarStream::RecordLiveData -> Entering LeddarStartRecording" << endl;
    CheckError( LeddarStartRecording( this->gHandle, temp_file ) );
//    cout << "LeddarStream::RecordLiveData -> Exiting LeddarStartRecording" << endl;

    // Throw the thread into a sleeping loop until leddar device fails
    while ( isrunning && !isstopped
                && LeddarGetRecording(this->gHandle) == LD_SUCCESS) {
        QThread::msleep(200);
        QCoreApplication::processEvents();
    }

    //Stop The Recording
    LeddarStopRecording(this->gHandle);

    // Rename the file
    QFile::rename(QString(temp_file), QString::fromStdString(fileName));

    StopStream();
cout << "LeddarStream::RecordLiveData -> Exiting RecordLiveData" << endl;
}


/*********************************************************************
 * Function to read Leddar data from a file.
 *
 * We detect the next set of points detected by the sensor, and store
 * them in a 'float' 'vector'.  We then emit these points and their
 * identifying index.  We continue reading points until either there
 * are no more points available, this thread stops running, or this
 * thread is stopped.
 *
 * We step the handle through the file until either we reach the end
 * of the file or this thread is not running or is stopped.  For each
 * step, we detect the next set of points and store them in a 'float'
 * 'vector'.  We then emit these points and their identifying index.
***/
void LeddarStream::ReplayData( void )
{
cout << "Entering ReplayData" << endl;
    int currentRecordIndex;
    vector<float> dataPoints;
    unsigned int i, lCount;
    LdDetection lDetections[16];

    CheckError( LeddarStartDataTransfer( this->gHandle, LDDL_DETECTIONS ) );

    // Calculate the frame rate of the recording
    // base rate = 12800

    // Properties are the power to raise 2 to. e.g. Accumulation rate = 2 ^ PID_ACCUMULATION_EXPONENT
    double fps, baserate, accumulationexp, oversampleexp;
    LeddarGetProperty(this->gHandle, PID_ACCUMULATION_EXPONENT, 0, &accumulationexp);
    LeddarGetProperty(this->gHandle, PID_OVERSAMPLING_EXPONENT, 0, &oversampleexp);
    baserate = 12800;

    // Calculate the frames per second :  Measurement rate = base rate/accumulations/oversampling
    fps = baserate / pow(2, accumulationexp) / pow(2, oversampleexp);

    // Calculate time between recordings in milliseconds
    long msdelay = 1.0/fps * 1000;
    long nextFrameTime = getCurrentTime() + msdelay;

    while (LeddarStepForward(this->gHandle) != LD_END_OF_FILE && isrunning && !isstopped)
    {
        lCount = LeddarGetDetectionCount( this->gHandle );

        /******************************
         * Run some edge-case tests.
        ***/
        if (lCount == 0) {
            cout << "ERROR: ReadLiveData - NO POINTS DETECTED!" << endl;

            // The official Leddar documentation suggests sending LeddarGetDetections to
            // a callback function.  Otherwise, the documentation suggests that we are
            // "not guranteed to get coherent data."  We could not get the callback working
            // with our Qt object-oriented structure.  Instead, I have determined that the
            // only likely data incoherence involves receiving random 0 vectors of points.
            // We 'continue' in case this is the case, so that we can later get actual data.
            continue;
        }
        if (lCount > ARRAY_LEN(lDetections)) {
            cout << "LeddarStream::ReadLiveData -> ERROR: ReadLiveData - More points detected than expected: " << lCount << endl;
//            continue;
            /***************
             * HOT FIX: At Distances > 10 meter > 16 points are always detected! I just shrink lCount to 16
             */
            lCount = 16;

            // lCount = ARRAY_LEN( lDetections );
            // This was Leddar's default behavior.  I guess they're really bad testers, eh?
        } else if (lCount < ARRAY_LEN(lDetections)) {
            // TODO: What do we do in the situation where we get fewer points than expected?
            // This can happen if the sensor is partially covered, or alternatively if the
            // sensor sees half of a wall.  Right now we 'continue' so that we don't get a
            // major crash.
            cout << "LeddarStream::ReadLiveData -> ERROR: ReadLiveData - Fewer points detected than expected: " << lCount << endl;
            continue;
        } else {
            cout << "ReadLiveData has exactly as many points as expected.";
        }
        /******************************/


        CheckError(LeddarGetDetections( this->gHandle, lDetections, ARRAY_LEN( lDetections ) ));

        // When replaying a record, display the current index
        cout << "Current Record size: "  << endl;

        if ( LeddarGetRecordSize( this->gHandle ) != 0 )
        {
            currentRecordIndex = LeddarGetCurrentRecordIndex(this->gHandle);
            cout << "Current Record Index: " << currentRecordIndex << endl;
        }

        // Output the detected points to the console.
        for( i=0; i < lCount; i++ )
        {
            cout << lDetections[i].mDistance << " ";
            // TODO: Check that the segment corresponds to index. Can they be out of order?
            dataPoints.push_back(lDetections[i].mDistance);
        }
        cout << endl;

        // Signal the detected points to the GUI.
        if (dataPoints.size() != 0) {
            emit this->sendDataPoints(currentRecordIndex, dataPoints, orientation);

            long thisFrameTime = getCurrentTime();
            if (thisFrameTime < nextFrameTime ) {
                QThread::msleep(nextFrameTime - thisFrameTime);
            }
            nextFrameTime = getCurrentTime() + msdelay;
        }
        dataPoints.erase(dataPoints.begin(), dataPoints.end());
        QCoreApplication::processEvents();
    }
    // Emit zeros
//    ClearData();
    cout << "Exiting ReplayData" << endl;

    LeddarStopDataTransfer(this->gHandle);
    StopStream();

    return;
cout << "Exiting ReplayData" << endl;
}


/*********************************************************************
 * Function that issues a stop recording command
 *
 * This function is necessary because of the atomic nature
 *
***/
void LeddarStream::StopRecord()
{
    if ( LeddarGetRecording(this->gHandle) == LD_SUCCESS)
    {
        LeddarStopRecording(this->gHandle);
        cout << "LeddarStream::StopRecord -> Stopped Recording" << endl;
    }
}



/*********************************************************************
 *********************************************************************
                           HELPER FUNCTIONS
 *********************************************************************
 *********************************************************************/



/*********************************************************************
 * Function to check for an error in a Leddar command.
 *
 * This function prints out the error code to console for any
 * unsuccessful Leddar library function.
***/
void LeddarStream::CheckError( int aCode )
{
    if ( aCode != LD_SUCCESS )
    {
        printf( "LeddarC error (%d): ", aCode );

        switch ( aCode )
        {
            case LD_ACCESS_DENIED : printf("ACCESS DENIED\n" ); break;
            case LD_TIMEOUT : printf("TIMEOUT\n" ); break;
            case LD_START_OF_FILE : printf("THAT IS THE START OF FILE\n" ); break;
            case LD_END_OF_FILE : printf("THIS IS THE END OF FILE\n" ); break;
            case LD_NO_RECORD : printf("THERE IS NO RECORD\n" ); break;
            case LD_ALREADY_STARTED : printf("ALREADY STARTED\n" ); break;
            case LD_NO_DATA_TRANSFER : printf("NO DATA TRANSFER\n" ); break;
            case LD_NOT_CONNECTED : printf("NOT CONNECTED\n" ); break;
            case LD_INVALID_ARGUMENT : printf("THAT IS AN INVALID ARGUMENT\n" ); break;
            case LD_ERROR : printf("ERROR\n" ); break;
            case LD_NOT_ENOUGH_SPACE : printf("THERE IS NOT ENOUGH SPACE\n" ); break;
        }
    }
}


/*********************************************************************
 * Function to list the address of all sensors available.
 *
 * This was the extent of the documentation in the LeddarCDemo.
 * More to come.
***/
void LeddarStream::ListSensors( char* aConnectyionType, char* aAddresses, unsigned int aSize )
{

cout << "Entering ListSensors" << endl;
    char         lConnectionType[256];
    unsigned int lIndex = 0;

    if ( aConnectyionType == NULL )
    {
        std::cout << "Enter the connection type (USB or SERIAL):" << endl;
        scanf("%255s", lConnectionType );
    }
    else
    {
        strcpy( lConnectionType, aConnectyionType );
    }

    strcpy( aAddresses, aConnectyionType );

    CheckError( LeddarListSensors( aAddresses, &aSize ) );

    std::cout << "Found " << aSize << " sensors of type " << lConnectionType << endl;
    std::cout << aAddresses << std::endl;

    int lConnectionFoundIndex = 0;
    while( strlen( aAddresses+lIndex ) > 0 )
    {
        if ( lConnectionFoundIndex % 2 == 0 )
        {
            if ( strcmp( aConnectyionType, "USB" ) != 0 )
            {
                printf( "%d : %s", lConnectionFoundIndex/2, aAddresses + lIndex );
            }
            else
            {
                printf( "%d : ", lConnectionFoundIndex/2 );
            }
        }
        else
        {
            if ( strcmp( aConnectyionType, "USB" ) != 0 )
            {
                printf( "\t[ %s ]\n", aAddresses + lIndex );
            }
            else
            {
                printf( "[ %s ]\n", aAddresses + lIndex );
            }
        }

        lConnectionFoundIndex++;
        lIndex += strlen( aAddresses+lIndex ) + 1;
    }
cout << "Exiting ListSensors" << endl;
}


/*********************************************************************
 * Function to find an address by index.
 *
 * We get the address found by the 'aIndex' displayed in the function 'ListSensors'.
 *
 * Input:
 *   aIndex - index of the sensor to find
 *   aAddresses - list of addresses.
 *
 * Returns:
 *   Address of the sensor,
 *   NULL if there is no address found for this index.
***/
char* LeddarStream::FindAddressByIndex( unsigned int aIndex, char* aAddresses )
{
cout << "Entering FindAddressByIndex" << endl;
    unsigned int lCurrentIndex = 0;
    unsigned int lConnectionFoundIndex = 0;

    while( strlen( aAddresses+lCurrentIndex ) > 0 )
    {
        if ( ( lConnectionFoundIndex / 2 ) == aIndex )
        {
            return aAddresses + lCurrentIndex;
        }

        lConnectionFoundIndex++;
        lCurrentIndex += strlen( aAddresses+lCurrentIndex ) + 1;
    }
    return NULL;
cout << "Exiting FindAddressByIndex" << endl;
}


/**********************************************************************
 * Emits a vector of zeros through sendDataPoints so as to "clean up"
 * the read data page after data is collected.
 *
***/
void LeddarStream::ClearData(unsigned int count)
{
    vector<float> zeros(count, 0.0);
    emit this->sendDataPoints(0, zeros, orientation);
}

/*********************************************************************
 * Returns the time since epoch in milliseconds
 */
//
long LeddarStream::getCurrentTime()
{
    long ms = chrono::duration_cast< chrono::milliseconds> (
                chrono::system_clock::now().time_since_epoch()).count();
    return ms;
}



/*********************************************************************
 *********************************************************************
                           PUBLIC SLOTS
 *********************************************************************
**********************************************************************/



/*********************************************************************
 * Slot to start streaming data from the LIDAR.
 *
 * We establish that this thread is running, has not been stopped,
 * and emit that it is running to the main thread.
 *
 * We then perform the streaming from the LIDAR sensor.
***/
void LeddarStream::StartStream()
{
cout << "Entering StartStream" << endl;
    if (isrunning) return;
    isstopped = false;
    isrunning = true;

    isReplay = false;
    isRecording = false;
    emit running();
    doStream();
cout << "Exiting StartStream" << endl;
}


/*********************************************************************
 * Slot to start replaying data from a file.
 *
 * We establish that this thread is running, has not been stopped,
 * and emit that it is running to the main thread.
 *
 * We then perform the reading from a file.
***/
void LeddarStream::StartReplay(string filename)
{
cout << "Entering StartReplay" << endl;
    if (isrunning) return;
    isstopped = false;
    isrunning = true;

    isReplay = true;
    isRecording = false;
    emit running();
    doReplay(filename);
cout << "Exiting StartReplay" << endl;
}


/*********************************************************************
 * Slot to start streaming data from the LIDAR.
 *
 * We establish that this thread is running, has not been stopped,
 * and emit that it is running to the main thread.
 *
 * We then perform the streaming from the LIDAR sensor.
***/
void LeddarStream::StartRecord(string fileName)
{
cout << "Entering StartRecord" << endl;
    if (isrunning || !isstopped) return;
    isstopped = false;
    isrunning = true;
    emit running();

    isReplay = false;
    isRecording = true;
    doStream(fileName);
cout << "Exiting StartRecord" << endl;
}


/*********************************************************************
 * Slot to stop streaming data from the LIDAR.
 *
 * We establish that this thread is not running, has been stopped,
 * and emit that it has been stopped to the main thread.
***/
void LeddarStream::StopStream()
{
cout << "Entering StopStream" << endl;
    if (!isrunning || isstopped) return;
    isstopped = true;
    isrunning = false;

    isReplay = false;
    isRecording = false;
    StopRecord();
    emit stopped();
//    ClearData();
cout << "Exiting StopStream" << endl;
}


/**********************************************************************
 * Set the orientation of the Leddar. Default orientation is Vertical
 *
***/
void LeddarStream::setOrientation(bool aOrientation)
{
//    cout << "EMISSION RECEIVED " << aOrientation << endl;
    orientation = aOrientation;
}



/*********************************************************************
 *********************************************************************
                           PRIVATE SLOTS
 *********************************************************************
**********************************************************************/



/*********************************************************************
 * Function to replay a Leddar file.
 *
 * We create a leddar handle and try to connect to a Leddar record file.
 * We close up by disconnecting and destroying our handle.
***/
void LeddarStream::doReplay(string fileName)
{
cout << "Entering doReplay" << endl;
    if (!isrunning || isstopped) return;

    cout << fileName<< endl;

    char* lName = const_cast<char*>(fileName.c_str());

    // Load the file record.
    if ( LeddarLoadRecord( this->gHandle, lName ) == LD_SUCCESS )
    {
        // For a big file, especially if it is on a network drive, it may
        // take a while before the replay is 100% ready. Note that you
        // can still use the replay but it will not report the complete
        // size until it is finished loading.
        while( LeddarGetRecordLoading( this->gHandle ) )
        {
            LeddarSleep( 0.5 );
        }

        ReplayData();
        LeddarDisconnect(this->gHandle);
    }
    else
    {
        cout << "Failed to load file!" << endl;
    }

    StopStream();

cout << "Exiting doReplay" << endl;
}


/*********************************************************************
 * Function to stream from the LIDAR sensor.
 *
 * We create a leddar handle and try to connect to a single USB sensor
 * by sending an empty string as the address.
 *
 * After connecting and streaming live, we then disconnect and destroy
 * our handle.
 *
 * NOTE: This connection will only work if there is exactly 1 USB sensor
 * plugged into the PC.
***/
void LeddarStream::doStream(string fileName)
{
cout << "LeddarStream::doStream -> Entering doStream" << endl;

    char lAddresses[256];
    char* lAddress = NULL;
    char lConnectionType[10];

    if (!isrunning || isstopped) return;

    strcpy( lConnectionType, "USB" );
    ListSensors( lConnectionType, lAddresses, 255 );
    lAddress = FindAddressByIndex( 0, lAddresses );
    if ( lAddress == NULL ) {
        cout << "NULL ADDRESS" << endl;
        return;
    }
    if ( LeddarConnect( this->gHandle, lConnectionType, lAddress ) == LD_SUCCESS )
    {
        cout << "LeddarStream::doStream -> LeddarConnection Successful" << endl;
        if (LeddarGetConnected(this->gHandle) == LD_SUCCESS && isrunning && !isstopped) {

            if ( isRecording ) {
                cout << "LeddarStream::doStream -> We are Recording" << endl;
                RecordLiveData(fileName);
            }
            else {
                ReadLiveData();
            }
        }
    }
    else
    {
        cout << "Connection Failed!" << endl;
    }

    LeddarDisconnect( gHandle );

cout << "LeddarStream::doStream -> Exiting doStream" << endl;
}



// End of file leddarthread.cpp
