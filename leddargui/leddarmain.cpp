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

    this->gHandle = NULL;
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

void LeddarStream::DataCallback( void *aHandle )
{
    LdDetection lDetections[50];
    unsigned int i, j, lCount = LeddarGetDetectionCount( aHandle );

    if ( lCount > ARRAY_LEN( lDetections ) )
    {
        lCount = ARRAY_LEN( lDetections );
    }

    LeddarGetDetections( aHandle, lDetections, ARRAY_LEN( lDetections ) );

    // When replaying a record, display the current index
    if ( LeddarGetRecordSize( this->gHandle ) != 0 )
    {
        printf( "%6d ", LeddarGetCurrentRecordIndex( this->gHandle ) );
    }

    for( i=0, j=0; (i<lCount) && (j<12); ++i )
    {
        printf( "%5.2f ", lDetections[i].mDistance );
        ++j;
    }
    puts( "" );

}

// *****************************************************************************
// Function: ReadLiveData
//
/// \brief   Start data transfer until a key is pressed and stop it (data is
///          displayed by the callback).
// *****************************************************************************

void LeddarStream::ReplayData( void )
{
    puts( "\nF to go forward, B to go backward, R to return to beginning, Q to quit" );

    CheckError( LeddarStartDataTransfer( this->gHandle, LDDL_DETECTIONS ) );

    //void (LeddarStream::*DataCallback)(void) = &LeddarStream::DataCallback;
    LeddarSetCallback( this->gHandle, reinterpret_cast<LdCallback>(&LeddarStream::DataCallback), this->gHandle );

    for(;;)
    {
        char lChoice = WaitKey();

        switch( lChoice )
        {
            case 'R':
                LeddarMoveRecordTo( this->gHandle, 0 );
                break;
            case 'B':
                CheckError( LeddarStepBackward( this->gHandle ) );
                break;
            case 'F':
                CheckError( LeddarStepForward( this->gHandle ) );
                break;
            case 'Q':
            case  27: // Escape
                LeddarStopDataTransfer( this->gHandle );
                LeddarRemoveCallback( this->gHandle, reinterpret_cast<LdCallback>(&LeddarStream::DataCallback), this->gHandle );
                return;
        }

        QCoreApplication::processEvents();
    }
}

// *****************************************************************************
// Function: ReplayMenu
//
/// \brief   Main menu when a replay a record file.
// *****************************************************************************

void LeddarStream::ReplayMenu( void )
{
    LeddarChar lName[256];

    // Ask for file name and try to load record before display menu.
    cout << "\nEnter file name: " << endl;
    cin >> lName;

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

        printf( "Finished loading record of %d frames.\n", 
                LeddarGetRecordSize( this->gHandle ) );

        for(;;)
        {
            char lChoice;

            puts( "\nReplay Menu" );
            puts( "  1. Read Data" );
            puts( "  2. Go Back to File Input" );

            lChoice = WaitKey();

            switch( lChoice )
            {
                case '1':
                    ReplayData();
                    break;
                case '2':
                case  27:
                    LeddarDisconnect( this->gHandle );
                    return;
            }
            QCoreApplication::processEvents();
        }
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
    for(;;)
    {
        cout << "Main menu for loop" << endl;
    	ReplayMenu(); 
        QCoreApplication::processEvents();
    }
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

    cout << "After LeddarCreate" << endl;
    MainMenu();

    cout << "After MainMenu" << endl;

    LeddarDestroy(this->gHandle);
    emit this->finished();

    return 0;
}

// End of file Main.c
