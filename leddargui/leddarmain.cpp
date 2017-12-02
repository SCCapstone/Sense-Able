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
// Function: DataCallback
//
/// \brief   This is the function that is called when a new set of data is
///          available. Here we simply display the first 12 detections.
///
/// \param   aHandle  This is the user data parameter that was passed to
///                   LeddarAddCallback. Here by design we know its the handle.
/// \param   aLevels  A bitmask of the data levels received in that frame.
///
/// \return  Non zero to be called again (responding 0 would remove this
///          function from the callback list).
// *****************************************************************************

void LeddarStream::DataCallback(void* aHandle )
{
cout << "Function DataCallback" << endl;
    int currentRecordIndex;
    vector<float> dataPoints;
    LdDetection lDetections[50];
    unsigned int i, j, lCount = LeddarGetDetectionCount( aHandle );
    if ( lCount > ARRAY_LEN( lDetections ) )
    {
        lCount = ARRAY_LEN( lDetections );
    }

    CheckError(LeddarGetDetections( aHandle, lDetections, ARRAY_LEN( lDetections ) ));

    // When replaying a record, display the current index

    if ( LeddarGetRecordSize( aHandle ) != 0 )
    {
        currentRecordIndex = LeddarGetCurrentRecordIndex(aHandle);
        cout << currentRecordIndex << endl;
    }

    // Output the detected points to the console.
    for( i=0, j=0; (i<lCount) && (j<12); ++i )
    {
        cout << lDetections[i].mDistance << " ";
        dataPoints.push_back(lDetections[i].mDistance);
        ++j;
//        QCoreApplication::processEvents();
    }
    cout << endl;

    emit openFileDialog(currentRecordIndex, dataPoints);
cout << "Function DataCallback finished" << endl;

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

    CheckError( LeddarStartDataTransfer( this->gHandle, LDDL_DETECTIONS ) );

    //void (LeddarStream::*DataCallback)(void) = &LeddarStream::DataCallback;
    //auto bindDataCallBack = std::bind(&LeddarStream::DataCallback, this, 95, std::placeholders::_1);
    LeddarSetCallback(this->gHandle, LeddarStream::DataCallback, this->gHandle);

    while (LeddarStepForward(this->gHandle) != LD_END_OF_FILE)
    {
cout << "Step forward" << endl;
        QCoreApplication::processEvents();
cout << "Step forward finished" << endl;
    }

    LeddarStopDataTransfer(this->gHandle);
    LeddarRemoveCallback( this->gHandle, LeddarStream::DataCallback, this->gHandle );
    return;
}

// *****************************************************************************
// Function: ReplayMenu
//
/// \brief   Main menu when a replay a record file.
// *****************************************************************************

void LeddarStream::ReplayMenu( void )
{
cout << "Function ReplayMenu" << endl;
    string inputString = "LeddarData/WALL.ltl";
    char* lName = new char[inputString.size() + 1];
    std::copy(inputString.begin(), inputString.end(), lName);
    lName[inputString.size()] = '\0';

    if ( LeddarLoadRecord( this->gHandle, lName ) == LD_SUCCESS )
    {
        puts( "\nPlease wait while the record is loading..." );

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
        puts( "\nFailed to load file!" );
    }
}

// *****************************************************************************
// Function: MainMenu
//
/// \brief   Display and responds to the main menu.
// *****************************************************************************

void LeddarStream::MainMenu()
{
cout << "Main menu" << endl;
    cout << "Main menu" << endl;
    ReplayMenu();
}

// *****************************************************************************
// Function: main
//
/// \brief   Standard C entry point!
// *****************************************************************************

int LeddarStream::leddarmain() {
//leddarmain()
    cout << "****************************************************" << endl;
    cout << "* Welcome to the LeddarC Simulation Replay Program *" << endl;
    cout << "****************************************************" << endl;

    this->gHandle = LeddarCreate();
//    *(this->gHandle) = LeddarCreate();

    cout << "After LeddarCreate" << endl;
    MainMenu();

    cout << "After MainMenu" << endl;

    LeddarDestroy(this->gHandle);
    emit this->finished();

    return 0;
}

// End of file Main.c
