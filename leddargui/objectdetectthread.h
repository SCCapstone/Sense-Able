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
    vector<float> xaxis_projection(vector<float> distances);

    vector<float> polynomial_fit(int polynom_degree, vector<float> points, vector<float> xvalues);
    float fit_quality(vector<float> coefficients, int polynom_degree, vector<float> points, vector<float> xvalues);

    float detectWall(vector<float> distances);
    float detectCorner(vector<float> distances);
    float detectPillar(vector<float> distances);
    float detectTripHazard(vector<float> distances);

public slots:
    void StartDetect(int index, vector<float> distances, bool aOrientation);
    void StopDetect();
    void SetSignalDist(float sig_dist);

private slots:
    void doDetect(vector<float> dataPoints, bool aOrientation);

signals:
    void emitDetectedObject(int object);
    void finished();
    void running();
    void stopped();

private:
    bool isrunning, isstopped;
    float sig_dist;
};

#endif // OBJECTDETECT_H
