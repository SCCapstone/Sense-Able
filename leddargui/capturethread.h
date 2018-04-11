#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <chrono>
using namespace std;

class CaptureThread : public QObject
{
    Q_OBJECT
public:
    CaptureThread();
    ~CaptureThread();

//    void run();
    int imagedetect(cv::HOGDescriptor, cv::Mat);
    void overlayDistance(cv::Mat frame);

    // Helper Functions
    void emitDefaultFrame();
    long getCurrentTime();

    cv::VideoCapture cap;
    cv::VideoWriter videoWriter;
    cv::Mat frame, defaultImage;

    string defaultImageFile;

    bool isrunning, isstopped;
    bool isRecording;
    std::vector<float> detections;

public slots:
    void StartCapture(string videoStream);
    void StopCapture();
    void StartRecord(string videoStream, string videFileName);

private slots:
    void doCapture(string videoFileName = "");
    void catchDetections(int index, std::vector<float> dataPoints, bool aOrientation);

signals:
    void emitFrame(cv::Mat*);

    // QThread "under the hood" signals
    void running();
    void stopped();
    void cancel();

};

#endif // CAPTURETHREAD_H
