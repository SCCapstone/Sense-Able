#include <vector>
using namespace std;

#include <QObject>
#include <QString>

#include "usernotifier.h"


class ObjectDetector
{
public:
//    ObjectDetector();
//    ~ObjectDetector();

    int detect_wall(vector<float> v, float measure_error, float flat_error);
    void signal(int object);

public slots:
    void DetectObject(vector<float> distances, float sig_dist);

signals:
    void finished();
};
