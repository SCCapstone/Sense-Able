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
    void run();
    int imagedetect(cv::HOGDescriptor, cv::Mat);
    void overlayDistance(std::vector<float> distances, cv::Mat frame);

    cv::VideoCapture cap;
    cv::VideoWriter videoWriter;
    cv::Mat frame;
    string defaultImage = "/home/jms/Documents/School/Sense-Able/LeddarData/default.jpg";

    bool isrunning, isstopped;
    bool isRecording;
    std::vector<float> distances;

public slots:
    void StartCapture(string videoStream);
    void StopCapture();

    void StartRecord(string videoStream, string videFileName);

private slots:
    void doCapture(string videoFileName = "");
    void captureDataPoints(int index, std::vector<float> dataPoints, bool aOrientation);

signals:
    void newFrame(cv::Mat*);
    void running();
    void stopped();
    void cancel();
//    void finished();

private:
    // Helper Functions
    void emitEmptyFrame();
    long getCurrentTime();

};

#endif // CAPTURETHREAD_H
