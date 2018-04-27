/*********************************************************************
 * Class for capturing webcam data.
 *
 * Date last modified: 11 April 2018
 * Author: Kathryn Vincent, Jonathan Senn
***/

#include <QCoreApplication>
#include <QDebug>

#include "capturethread.h"



/*********************************************************************
 *********************************************************************
                           PUBLIC
 *********************************************************************
**********************************************************************/


/*********************************************************************
 * The usual constructor.
 *
 * At initialization, we establish that this thread is not running,
 * and has not been stopped.
***/
CaptureThread::CaptureThread()
{
    isstopped = true;
    isrunning = false;

    defaultImageFile = "../LeddarData/default.png";
    defaultImage = cv::imread(defaultImageFile);
}
/*********************************************************************
 * The usual deconstructor
***/
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
void CaptureThread::overlayDistance(cv::Mat frame) {

    if (detections.size() == 0) return;

    float max_dist = 10.;
    int height = frame.size().height;
    int width = frame.size().width;

    int segments = int(detections.size());
    int seg_dist = width/segments; //Truncates but this shouldn't be noticeable. Also it doesn't matter.

    for (int i=0; i<segments; i++) {
        float distance = detections.at(i);

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
 *********************************************************************
                           HELPER FUNCTIONS
 *********************************************************************
**********************************************************************/


/*********************************************************************
 * Emits the default frame
 */
void CaptureThread::emitDefaultFrame()
{
    cout << "emitting" << endl;
    emit(emitFrame(&defaultImage));
}

/*********************************************************************
 * Returns the time since epoch in milliseconds
 */
//
long CaptureThread::getCurrentTime()
{
    long ms = chrono::duration_cast< chrono::milliseconds> (
                chrono::system_clock::now().time_since_epoch()).count();
    return ms;
}



/*********************************************************************
 *********************************************************************
                           PUBLIC SLOTS
 *********************************************************************
**********************************************************************/


/*********************************************************************
 * Slot to start this thread.
 *
 * We establish that this thread is running, has not stopped, and emit that
 * it is running to the main thread. If the camera has not been opened, we
 * also open the camera.
 *
 * We then proceed with performing the camera capture.
***/
void CaptureThread::StartCapture(string videoStream)
{
    if (isrunning) return;
    isstopped = false;
    isrunning = true;

    emit running();

    isRecording = false;

    cap.open(videoStream);
    doCapture();
}

/*********************************************************************
 * Slot to stop this thread.
 *
 * We establish that this thread is not running, and has been stopped.
 * We emit that it has been stopped to the main thread.
***/
void CaptureThread::StopCapture()
{
    if (!isrunning ) return;
    isstopped = true;
    isrunning = false;

    cap.release();
    if (isRecording) {
        videoWriter.release();
    }
    // Emit an default frame
    emitDefaultFrame();
    emit stopped();

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
void CaptureThread::StartRecord(string videoStream, string videoFileName)
{
    if (isrunning) return;
    isstopped = false;
    isrunning = true;
    emit running();

    isRecording = true;

    cap.open(videoStream);
    doCapture(videoFileName);
}



/*********************************************************************
 *********************************************************************
                           PRIVATE SLOTS
 *********************************************************************
**********************************************************************/


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
void CaptureThread::doCapture(string videoFileName)
{
    if (!isrunning || isstopped) return;

    // Get the frame rate of the video stream and calculate required delay
    int fps = cap.get(CV_CAP_PROP_FPS);
    long msdelay = 1.0/cap.get(CV_CAP_PROP_FPS) * 1000;

//    cout << "CaptureThread::doCapture -> FPS: " << fps << endl;
//    cout << "CaptureThread::doCapture -> Delay: " << msdelay << endl;

//    cv::HOGDescriptor hog;
//    hog.load("../my_detector.yml"); 

    // If save file is specified, construct a writing video stream.
    if ( isRecording  && cap.isOpened()) {

        cout << "CaptureThread::doCapture -> CaptureThread is recording" << endl;

        int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

        // Create the stream, encoded as Mjpeg. For other encodings see: https://www.fourcc.org/
        videoWriter.open(videoFileName, CV_FOURCC('M', 'J', 'P', 'G'),
                         fps, cv::Size(frame_width, frame_height));
    }

    // Later we will use this to time throttle the replay speed.
    long nextFrameTime = getCurrentTime() + msdelay;

    while(isrunning && !isstopped){

        // Check that Video Stream is open
        if( cap.isOpened() ) {

            cap >> frame;

            // Check that frame is not empty
            if ( !frame.empty() ) {

                // Write to file if file is specified
                if ( isRecording ) {
                    // save frame to file
                    videoWriter.write(frame);
                }

    //            int a = imagedetect(hog, frame);

                if ( !isRecording ) {
                    // Draw the heatmap and distances on to the frame and emit
                    overlayDistance(frame);
                }

                // TODO:: Draw "Recording" and recording dot
                emit(emitFrame(&frame));

                // Get the current time and compare to the expected "next frame time"
                // If the we arrive earlier than expected, wait
                long thisFrameTime = getCurrentTime();
                if (thisFrameTime < nextFrameTime){
                    QThread::msleep( nextFrameTime - thisFrameTime);
                }
                nextFrameTime = getCurrentTime() + msdelay;
            }
            else {
                // Lets start emiting a default frame
                cout << "Empty Frame" << endl;
                StopCapture();
            }
        } // if ( !frame.empty() ) {
        else{
            qDebug()<<"\nCamera not detected or is already in use. \nClose any other applications using the camera and try again.";
            StopCapture();
        }
        QCoreApplication::processEvents();
    }
}

/*********************************************************************
 * Slot to receive data points from leddar thread
 *
 * Set class variable distances to the newly received dataPoints.
 ****/
void CaptureThread::catchDetections(int index, std::vector<float> points, bool aOrientation){
    if(isrunning && !isstopped){
        //Draw stuff on frame
        detections.empty();
        detections = points;
//        cout << "CaptureThread::captureDataPoints -> capturing points in capture thread";
    }
}


// End of file capturethread.cpp
