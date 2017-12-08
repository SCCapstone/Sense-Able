//#include <QThread>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

#include "capturethread.h"

/*
 * Constructor for the capture thread. Opens the webcam
 */
CaptureThread::CaptureThread()
{

    //0: opens webcam
    //this->cap.open(0);
    isstopped = false;
    isrunning = false;
}
CaptureThread::~CaptureThread()
{
    return;
}
/*
 * This fuction takes an image and a image detector, detects which objects are present
 * and paints bounding boxes over the objects. An integer representing what object is
 * also returned.
 * Hog is a preloaded, pretrained HOG based image detector.
 */
int CaptureThread::imagedetect(cv::HOGDescriptor hog, cv::Mat frame){

    if ( frame.empty() ){
        return -1;
    }
    std::vector< cv::Rect > detections;
    std::vector< double > foundWeights;
    //TODO: ADJUST THESE PARAMETERS

    double hitThreshold = 0; // Default value
    cv::Size winStride = cv::Size(48,48);

    hog.detectMultiScale( frame, detections, foundWeights, hitThreshold, winStride);

    if (foundWeights.size() == 0) {
        std::cout << "WARNING: foundWeights is empty!  foundWeights.size() == 0!  Jonathan fix this!" << std::endl;
        return 0;
    }

    int max = 0;
    for (size_t i = 0; i < foundWeights.size(); i++) {
        if ( foundWeights.at(i) > foundWeights.at(max) ) {
            max = i;
        }
    }

    cv::Scalar color = cv::Scalar( 0, foundWeights.at(max) * foundWeights.at(max) * 200, 0);
    cv::rectangle( frame, detections.at(max), color, 2);

    return 0;
}

/*
 * TODO: Timer

void CaptureThread::run()
{
    timr = new QTimer(this);
    connect(timr, SIGNAL(timeout()), this, SLOT(doCapture()));
    timr -> start(10);
}
*/

void CaptureThread::doCapture()
/*
 * Captures image from camera and passes frames to the Gui for display
 * Loads a hardcoded image detector and passes every frame of the the camera feed to
 * CaptureThread::imagedetect(). Sends the results to the QT Gui
 */
{
    if (!isrunning || isstopped) return;

    cv::HOGDescriptor hog;
    hog.load("my_detector.yml");

    while(isrunning && !isstopped){
        if(cap.isOpened()){
            cap >> frame;
            int a = imagedetect(hog, frame);
            emit(newFrame(&frame));
        }
        else{
            qDebug()<<"camera not detected or is already in use";
            StopCapture();
        }
        QCoreApplication::processEvents();
    }

    QMetaObject::invokeMethod(this, "doCapture", Qt::QueuedConnection);
//    emit this->finished();
}

void CaptureThread::StartCapture() {
    if(!cap.isOpened()) cap.open(0);
    isstopped = false;
    isrunning = true;
    emit running();
    doCapture();
}

void CaptureThread::StopCapture() {
    isstopped = true;
    isrunning = false;
    emit stopped();
}
