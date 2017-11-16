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

    void CheckError(int aCode);
    char WaitKey(void);
    void DataCallback(void *aHandle);
    void ReplayData(void);
    void ReplayMenu(void);
    void MainMenu();

    LeddarHandle gHandle;

public slots:
    int leddarmain();

signals:
    void finished();
};

#endif // MAIN_H

