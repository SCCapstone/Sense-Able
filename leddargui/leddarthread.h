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

#include "globalconstants.h"

using namespace std;

#include "LeddarC.h"
#include "LeddarProperties.h"
class LeddarStream;

class LeddarStream : public QObject {
    Q_OBJECT

public:
    LeddarStream();
    ~LeddarStream();

    void ReadLiveData( void );
    void RecordLiveData(string fileName);
    void ReplayData(void);
    void StopRecord();

    // Helper functions
    static void CheckError(int aCode);
    void ListSensors( char* aConnectyionType, char* aAddresses, unsigned int aSize );
    char* FindAddressByIndex( unsigned int aIndex, char* aAddresses );
    void ClearData(unsigned int count = 16);
    long getCurrentTime();


    LeddarHandle gHandle;
    bool isrunning, isstopped;
    bool isReplay, isRecording;
    bool orientation = HORIZONTAL;

public slots:
    void StartStream();
    void StartReplay(string fileName);
    void StartRecord(string fileName);
    void StopStream();
    void setOrientation(bool aOrientation);

private slots:
    void doReplay(string fileName);
    void doStream(string fileName = "");

signals:
    void sendDataPoints(int index, vector<float> dataPoints, bool aOrientation);

    // QThread "under the hood" signals
    void finished();
    void running();
    void stopped();

};

#endif // MAIN_H

