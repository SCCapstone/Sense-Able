/*********************************************************************
 * Class for capturing webcam data.
 *
 * Date last modified: 8 December 2017
 * Author: Kathryn Vincent, Jonathan Senn
***/

//#include <QThread>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

#include "capturethread.h"

/*********************************************************************
 * The usual constructor.
 *
 * At initialization, we establish that this thread is not running,
 * and has not been stopped.
***/
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

/*********************************************************************
 * Function to perform image detection
 *
 * This fuction takes an image and a image detector, detects which objects are present
 * and paints bounding boxes over the objects. An integer representing what object is
 * also returned.
 *
 * Hog is a preloaded, pretrained HOG based image detector.
***/
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

    if (foundWeights.size() > 0) {

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
    std::cout << "No objects detected" << std::endl;
    return -1;
}

/*********************************************************************
 * Function to capture images from the webcamera.
 *
 * This function captures images from the camera and emits the frames
 * to the main thread to display on a window.
 *
 * We also load a hardcoded image detector and perform image detection on
 * every frame of the camera feed.  The results are also emitted to
 * the main thread for display.
***/
void CaptureThread::doCapture()

{
    if (!isrunning || isstopped) return;

    cv::HOGDescriptor hog;
    hog.load("../my_detector.yml");
//    std::cout  << hum << std::endl;
    while(isrunning && !isstopped){
        if(cap.isOpened()){
            cap >> frame;
            int a = imagedetect(hog, frame);
            emit(newFrame(&frame));
        }
        else{
            qDebug()<<"\nCamera not detected or is already in use. \nClose any other applications using the camera and try again.";
            emit(cancel());
            StopCapture();
        }
        QCoreApplication::processEvents();
    }

    QMetaObject::invokeMethod(this, "doCapture", Qt::QueuedConnection);
//    emit this->finished();
}

/*********************************************************************
 * Slot to start this thread.
 *
 * We establish that this thread is running, has not stopped, and emit that
 * it is running to the main thread. If the camera has not been opened, we
 * also open the camera.
 *
 * We then proceed with performing the camera capture.
***/
void CaptureThread::StartCapture() {
    if(!cap.isOpened()) cap.open(0);
    isstopped = false;
    isrunning = true;
    emit running();
    doCapture();
}

/*********************************************************************
 * Slot to stop this thread.
 *
 * We establish that this thread is not running, and has been stopped.
 * We emit that it has been stopped to the main thread.
***/
void CaptureThread::StopCapture() {
    isstopped = true;
    isrunning = false;
    emit stopped();
    cap.release();
}
