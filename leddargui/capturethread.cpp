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
    for ( size_t j = 0; j < detections.size(); j++ )
    {
//        cout << "Height " << detections[j].height << endl;
//        cout << "Width " << detections[j].width << endl;
//        cout << "X " << detections[j].x << endl;
//        cout << "Y " << detections[j].y << endl;
//        cout << "weight " << foundWeights[j] << endl;
        cv::Scalar color = cv::Scalar( 0, foundWeights[j] * foundWeights[j] * 200, 0 );
        cv::rectangle( frame, detections[j], color, 2);
    }
//    cv::rectangle( frame, cv::Point(100,100), cv::Point(200,200), cv::Scalar(0,0,0), 2);
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
