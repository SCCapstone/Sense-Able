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
    int detect_wall(vector<float> v, float measure_error, float flat_error);

public slots:

    void DetectObject(vector<float> distances, float sig_dist);
    void objDetect(int i);

signals:
    void objNotify(int o);
    void finished();
};

#endif // OBJECTDETECT_H
