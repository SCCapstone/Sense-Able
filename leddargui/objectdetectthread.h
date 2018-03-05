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
    vector<float> yaxis_projection(vector<float> distances);

public slots:
    void StartDetect(int index, vector<float> distances);
    void StopDetect();
    //void objDetect(int i);
    void SetSignalDist(float sig_dist);

private slots:
    void doDetect(vector<float> dataPoints);

signals:
    void sendObjectDetected(string objectName);
    void finished();
    void running();
    void stopped();

private:
    bool isrunning, isstopped;
    float sig_dist;
};

#endif // OBJECTDETECT_H
