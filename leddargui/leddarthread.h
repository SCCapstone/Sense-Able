/********************************************************************
 * Main header file for Milestone 3 Program
 * 
 * Author: Caleb Kisby
 * Date last modified: 14 October 2017
 * Date of conception: 14 October 2017
 * 
**/

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <QObject>
#include <QString>
using namespace std;

#include "LeddarC.h"
#include "LeddarProperties.h"
class LeddarStream;

class LeddarStream : public QObject {
    Q_OBJECT

public:
    LeddarStream();
    ~LeddarStream();

    static const bool VERTICAL = true; // Beam across x-axis --
    static const bool HORIZONTAL = false; // Beam across y-axis |

    static void CheckError(int aCode);
    char WaitKey(void);
    /*static void DataCallback(void *aHandle);*/
    void ReplayData(void);
    //void DataCallback( void *aHandle );
    void ReadLiveData( void );
    void RecordLiveData(string fileName);
    void StopRecord();
    void ListSensors( char* aConnectyionType, char* aAddresses, unsigned int aSize );
    char* FindAddressByIndex( unsigned int aIndex, char* aAddresses );

    // Helper function
    void ClearData(unsigned int count = 16);

    LeddarHandle gHandle;
    bool isrunning, isstopped;
    bool isReplay, isRecording;
    bool orientation = VERTICAL;

public slots:
//    void StartReplay(QString filename);
    void StartReplay(string fileName);
//    void StopReplay();
    void StartStream();
    void StopStream();
    void StartRecord(string fileName);
    void setOrientation(bool aOrientation);

private slots:
    void doReplay(string fileName);
    void doStream(string fileName = "");

signals:
    void finished();
    void sendDataPoints(int index, vector<float> dataPoints, bool aOrientation);
    void running();
    void stopped();

};

#endif // MAIN_H

