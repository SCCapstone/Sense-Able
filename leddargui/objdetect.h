#ifndef OBJECTDETECT_H
#define OBJECTDETECT_H

#include <vector>
#include <iostream>
using namespace std;

#include <QObject>
#include <QString>

#include "usernotifier.h"

class objectDetector : public QObject
{
        Q_OBJECT
public:
    objectDetector();

    void detectObject(vector<float> distances);
    int detect_wall(vector<float> v, float measure_error, float flat_error);

public slots:
    void processDataPoints(int index, vector<float> dataPoints);
    //void objDetect(int i);

signals:
    void sendObjectDetected(string objectName);
    void finished();
};

#endif // OBJECTDETECT_H
