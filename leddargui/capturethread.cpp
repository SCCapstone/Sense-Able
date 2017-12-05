//#include <QThread>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <QTimer>

#include "capturethread.h"

CaptureThread::CaptureThread()
{
    //0: opens webcam
    //this->cap.open(0);
}
CaptureThread::~CaptureThread()
{
    return;
}
int CaptureThread::imagedetect(cv::HOGDescriptor hog, cv::Mat frame){

    if ( frame.empty() ){
        return -1;
    }
    std::vector< cv::Rect > detections;
    std::vector< double > foundWeights;
    //TODO: ADJUST THESE PARAMETERS

    double hitThreshold = 0; // Default value
    cv::Size winStride = cv::Size(48,48);
//    cv::Size padding = Size(8,8);

    hog.detectMultiScale( frame, detections, foundWeights, hitThreshold, winStride);
    int max = 0;
    for (size_t i = 0; i < foundWeights.size(); i++) {
        if ( foundWeights.at(i) > foundWeights.at(max) ) {
            max = i;
        }
    }
    cv::Scalar color = cv::Scalar( 0, foundWeights[max] * foundWeights[max] * 200, 0 );
    cv::rectangle( frame, detections[max], color, 2);

    return 0;
}
void CaptureThread::run()
{
    timr = new QTimer(this);
    connect(timr, SIGNAL(timeout()), this, SLOT(startCapture()));

    timr -> start(10);
}

void CaptureThread::onStartCapture()
{
    cv::HOGDescriptor hog;
    hog.load("my_detector.yml");
    this->cap.open(0);

    while(true){
        if(cap.isOpened()){
            cap >> frame;
            int a = imagedetect(hog, frame);
            emit(newFrame(&frame));
        }
        else{
            std::cout<<"camera not detected";
        }
    }

    emit this->finished();
}
