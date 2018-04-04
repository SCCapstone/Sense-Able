#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <QTimer>

class CaptureThread : public QObject
{
    Q_OBJECT
public:
    CaptureThread();
    ~CaptureThread();
    void run();
    int imagedetect(cv::HOGDescriptor, cv::Mat);
    void overlayDistance(std::vector<float> distances, cv::Mat frame);

public slots:
    void StartCapture(int cameraNumber);
    void StopCapture();

private slots:
    void doCapture();
    void captureDataPoints(int index, std::vector<float> dataPoints, bool aOrientation);

signals:
    void newFrame(cv::Mat*);
    void running();
    void stopped();
    void cancel();
//    void finished();

private:
    QTimer* timr;
    cv::VideoCapture cap;
    cv::Mat frame;

    bool isrunning, isstopped;
    std::vector<float> distances;

};

#endif // CAPTURETHREAD_H
