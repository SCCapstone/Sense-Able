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

#include "leddarthread.h"

#include <QCoreApplication>
#include <QThread>
#include <QObject>
#include <functional>

#define ARRAY_LEN( a )  (sizeof(a)/sizeof(a[0]))

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
    isstopped = false;
    isrunning = false;
}

/*********************************************************************
 * The usual destructor.
***/
LeddarStream::~LeddarStream() {
    return;
}

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
 * Function to wait until a key is pressed.
 *
 * Note that we need to ping the sensor to keep the connection alive
 * while waiting for the key.
 *
 * Returns:
 *   The character corresponding to the key pressed (converted to uppercase)
***/
char LeddarStream::WaitKey( void )
{
    // LeddarGetKey is blocking so we need to wait for a key to be pressed
    // before calling it.
    while( !LeddarKeyPressed() )
    {
        LeddarSleep( 0.5 );
    }

    return toupper( LeddarGetKey() );
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
cout << "Function ReplayData" << endl;
    int currentRecordIndex;
    vector<float> dataPoints;
    unsigned int i, lCount;
    LdDetection lDetections[50];

    CheckError( LeddarStartDataTransfer( this->gHandle, LDDL_DETECTIONS ) );

    while (LeddarStepForward(this->gHandle) != LD_END_OF_FILE && isrunning && !isstopped)
    {
        lCount = LeddarGetDetectionCount( this->gHandle );
        if ( lCount > ARRAY_LEN( lDetections ) )
        {
            lCount = ARRAY_LEN( lDetections );
        }

        CheckError(LeddarGetDetections( this->gHandle, lDetections, ARRAY_LEN( lDetections ) ));

        // When replaying a record, display the current index

        if ( LeddarGetRecordSize( this->gHandle ) != 0 )
        {
            currentRecordIndex = LeddarGetCurrentRecordIndex(this->gHandle);
            cout << currentRecordIndex << endl;
        }

        // Output the detected points to the console.
        for( i=0; i < lCount; i++ )
        {
            cout << lDetections[i].mDistance << " ";
            dataPoints.push_back(lDetections[i].mDistance);
        }
        cout << endl;

        // Signal the detected points to the GUI.
        if (dataPoints.size() != 0) {
            emit this->sendDataPoints(currentRecordIndex, dataPoints);
            QThread::msleep(200);
        }
        dataPoints.erase(dataPoints.begin(), dataPoints.end());
        QCoreApplication::processEvents();
    }

    LeddarStopDataTransfer(this->gHandle);
    return;
}

// *****************************************************************************
// Function: ReplayMenu
//
/// \brief   Main menu when a replay a record file.
// *****************************************************************************

/*********************************************************************
 * Function to replay a Leddar file.
 *
 * We create a leddar handle and try to connect to a Leddar record file.
 * We close up by disconnecting and destroying our handle.
***/
void LeddarStream::doReplay(QString fileName)
{
    if (!isrunning || isstopped) return;

    cout << fileName.toUtf8().constData() << endl;

    // Initialize the Leddar Handle.
    this->gHandle = LeddarCreate();

    // TODO
    // We currently use a hard-coded filename.
    //string inputString = "LeddarData/WALL.ltl";
    //char* lName = new char[inputString.size() + 1];
    //std::copy(inputString.begin(), inputString.end(), lName);
    //lName[inputString.size()] = '\0';

    char* lName = const_cast<char*>(fileName.toUtf8().constData());

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


    // Destroy the handle, and signal that we are done.
    LeddarDestroy(this->gHandle);
//    QMetaObject::invokeMethod(this, "doReplay", Qt::QueuedConnection);
    StopReplay();
//    emit this->finished();
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
cout << "Start ReadLiveData" << endl;
    int currentRecordIndex;
    vector<float> dataPoints;
    unsigned int i, lCount;
    LdDetection lDetections[16];

    LeddarChar recordingFileName[255];

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
            cout << "ERROR: ReadLiveData - More points detected than expected!" << endl;
            break;

            // lCount = ARRAY_LEN( lDetections );
            // This was Leddar's default behavior.  I guess they're really bad testers, eh?
        } else if (lCount < ARRAY_LEN(lDetections)) {
            // TODO: What do we do in the situation where we get fewer points than expected?
            // This can happen if the sensor is partially covered, or alternatively if the
            // sensor sees half of a wall.  Right now we 'continue' so that we don't get a
            // major crash.
            cout << "ERROR: ReadLiveData - Fewer points detected than expected!" << endl;
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
        emit this->sendDataPoints(currentRecordIndex, dataPoints);

        dataPoints.erase(dataPoints.begin(), dataPoints.end());
        QCoreApplication::processEvents();
    }

    StopStream();
    LeddarStopDataTransfer( this->gHandle );
}

/*********************************************************************
 * Function to list the address of all sensors available.
 *
 * This was the extent of the documentation in the LeddarCDemo.
 * More to come.
***/
void LeddarStream::ListSensors( char* aConnectyionType, char* aAddresses, unsigned int aSize )
{
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

    std::cout << "Found " << aSize << "sensors of type " << lConnectionType << endl;

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
void LeddarStream::doStream()
{
    char lAddresses[256];
    char* lAddress = NULL;
    char lConnectionType[10];

    if (!isrunning || isstopped) return;

    // Initialize the Leddar Handle.
    this->gHandle = LeddarCreate();

    strcpy( lConnectionType, "USB" );
    ListSensors( lConnectionType, lAddresses, 255 );
    lAddress = FindAddressByIndex( 0, lAddresses );
    if ( lAddress == NULL ) {
        return;
    }

    if ( LeddarConnect( this->gHandle, lConnectionType, lAddress ) == LD_SUCCESS )
    {
        while( LeddarGetConnected( this->gHandle ) == LD_SUCCESS && isrunning && !isstopped)
        {
            ReadLiveData();
        }
    }
    else
    {
        cout << "Connection Failed!" << endl;
    }

    // Disconnect, destroy the handle, and signal that we are done.
    LeddarDisconnect( gHandle );
    LeddarDestroy(this->gHandle);

    QMetaObject::invokeMethod(this, "doStream", Qt::QueuedConnection);
//    emit this->finished();
}

/*********************************************************************
 * Slot to start replaying data from a file.
 *
 * We establish that this thread is running, has not been stopped,
 * and emit that it is running to the main thread.
 *
 * We then perform the reading from a file.
***/
void LeddarStream::StartReplay(QString filename) {
    isstopped = false;
    isrunning = true;
    emit running();
    doReplay(filename);
}

/*********************************************************************
 * Slot to stop replaying data from a file.
 *
 * We establish that this thread is not running, has been stopped,
 * and emit that it has been stopped to the main thread.
***/
void LeddarStream::StopReplay() {
    isstopped = true;
    isrunning = false;
    emit stopped();
}

/*********************************************************************
 * Slot to start streaming data from the LIDAR.
 *
 * We establish that this thread is running, has not been stopped,
 * and emit that it is running to the main thread.
 *
 * We then perform the streaming from the LIDAR sensor.
***/
void LeddarStream::StartStream() {
    isstopped = false;
    isrunning = true;
    emit running();
    doStream();
}

/*********************************************************************
 * Slot to stop streaming data from the LIDAR.
 *
 * We establish that this thread is not running, has been stopped,
 * and emit that it has been stopped to the main thread.
***/
void LeddarStream::StopStream() {
    isstopped = true;
    isrunning = false;
    emit stopped();
}

// End of file Main.c
