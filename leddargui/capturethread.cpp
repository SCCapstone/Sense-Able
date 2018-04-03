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
 * Function to overlay some distance rendering onto the fram
 *
 * This fuction takes an image and a set of points and displays the distance on the frame
 ***/
void CaptureThread::overlayDistance(std::vector<float> distances, cv::Mat frame) {

    float max_dist = 10.;
    int height = frame.size().height;
    int width = frame.size().width;

    int segments = int(distances.size());
    int seg_dist = width/segments; //Truncates but this shouldn't be noticeable. Also it doesn't matter.

    for (int i=0; i<segments; i++) {
        float distance = distances.at(i);

        // Normalize the distance from 0 - max distance
        float scaling_factor = distance / max_dist;
        if (scaling_factor > 1) {
            scaling_factor = 1.0;
        }
        cv::Scalar color = cv::Scalar(scaling_factor*255, 0, scaling_factor*-255 + 255);
            // Draw the rectangles
            cv::rectangle(frame,
                    cv::Point(seg_dist*i, height - 11),//upper left
                    cv::Point(seg_dist*i+seg_dist, height - 1), //lower right
                    color, //cv::Scalar( 0, 255, 255 ),
                -1);
        // Write the distance
        cv::putText(frame,
                   std::to_string(distance).substr(0,4),
                   cv::Point(seg_dist*i + 3, height - 16),
                   cv::FONT_HERSHEY_DUPLEX,
                   .45,
                   color, //cv::Scalar(0, 255, 255),
                   1.6);
    }
    return;
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

//    cv::HOGDescriptor hog;
//    hog.load("../my_detector.yml");

    while(isrunning && !isstopped){
        if(cap.isOpened()){
            cap >> frame;
//            int a = imagedetect(hog, frame);

            if (distances.size() > 5){
                overlayDistance(distances, frame);
            }
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
 * Slot to receive data points from leddar thread
 *
 * Set class variable distances to the newly received dataPoints.
 ****/
void CaptureThread::captureDataPoints(int index, std::vector<float> points){
    if(isrunning && !isstopped){
        //Draw stuff on frame
        distances.empty();
        distances = points;
        qDebug()<<"capturing points in capture thread";
    }
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
void CaptureThread::StartCapture(int cameraNumber) {
    if (isrunning) return;
    std::string cameraFileName = "/dev/video" + std::to_string(cameraNumber);
//    cameraFileName = "/home/jms/Documents/School/Sense-Able/LeddarData/video_doorway_1.mp4";
    if(!cap.isOpened()) cap.open(cameraFileName);
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
    if (!isrunning || isstopped) return;

    isstopped = true;
    isrunning = false;
    emit stopped();
    cap.release();
}
