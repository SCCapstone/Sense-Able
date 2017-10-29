#include "main.h"

/********************************************************************
 * Milestone 3 Main Program
 * 
 * Author: Caleb Kisby
 * Date of conception: 28 October 2017
 * Date last modified: 28 October 2017
 * 
 * Note: This code has been taken straight from the LeddarCDemo main program.
 * Some functions will be excluded for our purposes.
 * That program (and hence this code) is Copyright (c) 2013-2015 LeddarTech
 * Inc. All rights reserved.  We accept and agree to be bound to the terms of
 * the LeddarTech Inc. license agreement.
 * 
 * MAKE SURE YOU RUN THIS PROGRAM WITH PERMISSIONS ON YOUR MACHINE
 * THAT ALLOW YOU TO MANAGE USB DEVICES!
 * 
 * If you don't know what this means, then just 
 *   sudo ./ProgramName
 * 
**/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ARRAY_LEN( a )  (sizeof(a)/sizeof(a[0]))

// Global variable to avoid passing to each function.
static LeddarHandle gHandle=NULL;

// *****************************************************************************
// Function: CheckError
//
/// \brief   Check a return code and if it is not success, display an error
///          message corresponding to the code.
///
/// \param   aCode  The result code to verify.
// *****************************************************************************

static void
CheckError( int aCode )
{
    if ( aCode != LD_SUCCESS )
    {        
        printf( "LeddarC error (%d): ", aCode );

        switch ( aCode )
        {
            case LD_ACCESS_DENIED : printf("LD_ACCESS_DENIED\n" ); break;
            case LD_TIMEOUT : printf("LD_TIMEOUT\n" ); break;
            case LD_START_OF_FILE : printf("LD_START_OF_FILE\n" ); break;
            case LD_END_OF_FILE : printf("LD_END_OF_FILE\n" ); break;
            case LD_NO_RECORD : printf("LD_NO_RECORD\n" ); break;
            case LD_ALREADY_STARTED : printf("LD_ALREADY_STARTED\n" ); break;
            case LD_NO_DATA_TRANSFER : printf("LD_NO_DATA_TRANSFER\n" ); break;
            case LD_NOT_CONNECTED : printf("LD_NOT_CONNECTED\n" ); break;
            case LD_INVALID_ARGUMENT : printf("LD_INVALID_ARGUMENT\n" ); break;
            case LD_ERROR : printf("LD_ERROR\n" ); break;
            case LD_NOT_ENOUGH_SPACE : printf("LD_NOT_ENOUGH_SPACE\n" ); break;
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

static char
WaitKey( void )
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

static void
DataCallback( void *aHandle )
{
    LdDetection lDetections[50];
    unsigned int i, j, lCount = LeddarGetDetectionCount( aHandle );

    if ( lCount > ARRAY_LEN( lDetections ) )
    {
        lCount = ARRAY_LEN( lDetections );
    }

    LeddarGetDetections( aHandle, lDetections, ARRAY_LEN( lDetections ) );

    // When replaying a record, display the current index
    if ( LeddarGetRecordSize( gHandle ) != 0 )
    {
        printf( "%6d ", LeddarGetCurrentRecordIndex( gHandle ) );
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


// TODO Problem: We are not able to intercept the data and funnel it as it is
//      being read.  Read the manual to get a function to get what is currently
//      being read on 'gHandle'.

static void
ReadLiveData( void )
{
    LeddarChar recordingFileName[255];
    puts( "\nPress a key to start reading data and press a key again to stop." );
    WaitKey();

//    CheckError(LeddarStartRecording(gHandle, recordingFileName));
    CheckError( LeddarStartDataTransfer( gHandle, LDDL_DETECTIONS ) );
    LeddarSetCallback( gHandle, DataCallback, gHandle );

    WaitKey();

    LeddarStopDataTransfer( gHandle );
    LeddarRemoveCallback( gHandle, DataCallback, gHandle );
//    LeddarStopRecording(gHandle);
}

// *****************************************************************************
// Function: ListSensors
//
/// \brief   List the address of all sensors available.
// *****************************************************************************

static void
ListSensors( char* aConnectyionType, char* aAddresses, unsigned int aSize )
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

static char* 
FindAddressByIndex( unsigned int aIndex, char* aAddresses )
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

static void
ConnectMenu()
{
    char lAddresses[256];
    char* lAddress = NULL;
    char lConnectionType[10];
    
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
            char lChoice;
            
            cout << "1. Record Next Set of Real-Time Data" << "\n";
            cout << "2. Quit" << "\n";
            
            lChoice = WaitKey();

            switch( lChoice )
            {
                case '1':
                    ReadLiveData();
                    break;
                case '2':
                case  27:
                    LeddarDisconnect( gHandle );
                    return;
            }
        }
    }
    else
    {
        puts( "\nConnection failed!" );
    }    
}

// *****************************************************************************
// Function: main
//
/// \brief   Standard C entry point!
// *****************************************************************************

int
main( int argc, char *argv[] )
{
    puts( "*************************************************" );
    puts( "* Welcome to the LeddarC Demonstration Program! *" );
    puts( "*************************************************" );

    gHandle = LeddarCreateWithConsole( argc, argv );

    ConnectMenu();

    LeddarDestroy( gHandle );

    return 0;
}

// End of file Main.c
