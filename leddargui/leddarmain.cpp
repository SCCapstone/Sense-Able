// *****************************************************************************
// Module..: SDK -- Software development kit for Leddar products.
//
/// \file    Main.c
///
/// \brief   Simple console program demonstrating the use of Leddar Tech's
///					"read data" function
// Platform: Win32, Linux
//
// Copyright (c) 2013-2015 LeddarTech Inc. All rights reserved.
// Information contained herein is or may be confidential and proprietary to
// LeddarTech inc. Prior to using any part of the software development kit
// accompanying this notice, you must accept and agree to be bound to the
// terms of the LeddarTech Inc. license agreement accompanying this file.
//
// *****************************************************************************
//
//	DISCLAIMER: This program is a modified version of the leddar C Demo. It
//		has been modified to only use the read data function so that we  
//		can simply show that we read back data from our simulations as
//		well as show that we know how to take apart, analyze, and use 
//		the resources that are given to us.
//
//		This Program was modified by Austin Scampini
//
// *****************************************************************************

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "leddarmain.h"

#include <QCoreApplication>
#include <QThread>
#include <QObject>
#include <functional>

#define ARRAY_LEN( a )  (sizeof(a)/sizeof(a[0]))

// Global variable to avoid passing to each function.
//static LeddarHandle this->gHandle=NULL;
//QThread thread;

// *****************************************************************************
// Function: CheckError
//
/// \brief   Check a return code and if it is not success, display an error
///          message corresponding to the code.
///
/// \param   aCode  The result code to verify.
// *****************************************************************************

LeddarStream::LeddarStream() {

    this->gHandle = new LeddarHandle();
}

LeddarStream::~LeddarStream() {
    return;
}

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

// *****************************************************************************
// Function: WaitKey
//
/// \brief   Wait for a key to be pressed on the keyboard, pinging the sensor
///          to keep the connection alive while waiting.
///
/// \return  The character corresponding to the key pressed (converted to
///          uppercase for letters).
// *****************************************************************************

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

// *****************************************************************************
// Function: ReadLiveData
//
/// \brief   Start data transfer until a key is pressed and stop it (data is
///          displayed by the callback).
// *****************************************************************************

void LeddarStream::ReplayData( void )
{
cout << "Function ReplayData" << endl;
    int currentRecordIndex;
    vector<float> dataPoints;
    unsigned int i, j, lCount;
    LdDetection lDetections[50];

    CheckError( LeddarStartDataTransfer( this->gHandle, LDDL_DETECTIONS ) );

    while (LeddarStepForward(this->gHandle) != LD_END_OF_FILE)
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
        for( i=0, j=0; (i<lCount) && (j<12); ++i )
        {
            cout << lDetections[i].mDistance << " ";
            dataPoints.push_back(lDetections[i].mDistance);
            ++j;
        }
        cout << endl;

        // Signal the detected points to the GUI.
        emit this->sendDataPoints(currentRecordIndex, dataPoints);
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

void LeddarStream::StartReplay( void )
{
    // Initialize the Leddar Handle.
    this->gHandle = LeddarCreate();

    // TODO
    // We currently use a hard-coded filename.
    string inputString = "LeddarData/WALL.ltl";
    char* lName = new char[inputString.size() + 1];
    std::copy(inputString.begin(), inputString.end(), lName);
    lName[inputString.size()] = '\0';

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
    emit this->finished();
}

// *****************************************************************************
// Function: ReadLiveData
//
/// \brief   Start data transfer until a key is pressed and stop it (data is
///          displayed by the callback).
// *****************************************************************************


// TODO Problem: We are not able to intercept the data and funnel it as it is
//      being read.  Read the manual to get a function to get what is currently
//      being read on 'gHandle'.

void LeddarStream::ReadLiveData( void )
{
cout << "Start ReadLiveData" << endl;
    int currentRecordIndex;
    vector<float> dataPoints;
    unsigned int i, j, lCount;
    LdDetection lDetections[50];

    LeddarChar recordingFileName[255];

    CheckError( LeddarStartDataTransfer( gHandle, LDDL_DETECTIONS ) );

// Datacallback stuff **************************************************************************
    while (LeddarWaitForData(this->gHandle, 2000000) == LD_SUCCESS) {
cout << "Getting next data points" << endl;
        lCount = LeddarGetDetectionCount( this->gHandle );
cout << lCount << endl;
        if ( lCount > ARRAY_LEN( lDetections ) )
        {
            lCount = ARRAY_LEN( lDetections );
        }

        LeddarGetDetections( this->gHandle, lDetections, ARRAY_LEN( lDetections ));

        // When replaying a record, display the current index

        if ( LeddarGetRecordSize( this->gHandle ) != 0 )
        {
            currentRecordIndex = LeddarGetCurrentRecordIndex(this->gHandle);
            cout << currentRecordIndex << endl;
        }

        // Output the detected points to the console.
        for( i=0, j=0; (i<lCount) && (j<12); ++i )
        {
            cout << lDetections[i].mDistance << " ";
            dataPoints.push_back(lDetections[i].mDistance);
            ++j;
        }
        cout << endl;
cout << dataPoints.size() << endl;
        // Signal the detected points to the GUI.
        emit this->sendDataPoints(currentRecordIndex, dataPoints);

        dataPoints.erase(dataPoints.begin(), dataPoints.end());
        QCoreApplication::processEvents();
    }
// Datacallback done **************************************************************************

    LeddarStopDataTransfer( this->gHandle );
}

// *****************************************************************************
// Function: ListSensors
//
/// \brief   List the address of all sensors available.
// *****************************************************************************

void LeddarStream::ListSensors( char* aConnectyionType, char* aAddresses, unsigned int aSize )
{
    char         lConnectionType[256];
    unsigned int lIndex = 0;

    if ( aConnectyionType == NULL )
    {
        printf("\nEnter the connection type (USB or SERIAL): ");
        scanf("%255s", lConnectionType );
    }
    else
    {
        strcpy( lConnectionType, aConnectyionType );
    }

    strcpy( aAddresses, aConnectyionType );

    CheckError( LeddarListSensors( aAddresses, &aSize ) );

    printf( "\nFound %d sensors of type %s\n", aSize, lConnectionType );

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

// *****************************************************************************
// Function: FindAddressByIndex
//
/// \brief   Get the address found by the index displayed in the function ListSensors
//
//  \param  aIndex of the sensor to find
//  \param  aAddresses List of addresses.
//
//  \return Address of the sensor, NULL if there is no address found for this index.
//
// *****************************************************************************

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

// *****************************************************************************
// Function: ConnectMenu
//
/// \brief   Main menu when a live connection is made.
///
/// \param   aTrySingleUsb  If true we will try to connect to a single USB
///                         sensor by sending an empty string as the address.
///                         This works only if there is 1 and only 1 USB sensor
///                         plugged to the PC.
// *****************************************************************************

void LeddarStream::StartStream()
{
    char lAddresses[256];
    char* lAddress = NULL;
    char lConnectionType[10];

    // Initialize the Leddar Handle.
    this->gHandle = LeddarCreate();

    strcpy( lConnectionType, "USB" );
    ListSensors( lConnectionType, lAddresses, 255 );
    lAddress = FindAddressByIndex( 0, lAddresses );
    if ( lAddress == NULL ) {
        return;
    }

    if ( LeddarConnect( gHandle, lConnectionType, lAddress ) == LD_SUCCESS )
    {
        while( LeddarGetConnected( gHandle ) == LD_SUCCESS )
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
    emit this->finished();
}

// End of file Main.c
