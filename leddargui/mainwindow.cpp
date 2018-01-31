/*********************************************************************
 * The MainWindow class for the object detection Demo program.
 *
 * Date last modified: 8 December 2017
 * Author: Kathryn Vincent, Jonathan Senn, Austin Scampini, Caleb Kisby
***/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QObject>
#include <QtWidgets>
#include <QMetaType>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

/*********************************************************************
 * The usual constructor.
 *
 * This constructor creates a new QWidget Window (inherits from QWidget),
 * We associate threads for each possible action that might be done
 * within this window.  In particular, we have a 'stream' and corresponding
 * 'leddarThread' for reading Leddar data from a LIDAR or file, a
 *  'capture' and corresponding 'captureThread' for capturing webcam data,
 * and finally an 'objdetector' and corresponding 'objdetectThread' for
 * detecting an object whenever new data is found.
***/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->leddarThread = new QThread();
    this->stream = new LeddarStream;
    this->captureThread = new QThread();
    this->capture = new CaptureThread();

    this->objdetectThread = new QThread();
    this->objdetector = new objectDetector();

//    this->signalMapper = new QSignalMapper(this);

    // We connect the threads together via their signals and slots.

    // First, we connect the captureThread and the main thread
    // in order to display a video feed on the window.
    this->capture->moveToThread(captureThread);
    connect(this, SIGNAL(startCapture()), capture, SLOT(StartCapture()));
    connect(this, SIGNAL(stopCapture()), capture, SLOT(StopCapture()));
    connect(capture, SIGNAL(newFrame(cv::Mat*)), this, SLOT(frameCaptured(cv::Mat*)));

    // We then connect the leddar stream and main thread to allow the
    // window to display the data read in from the stream.
    this->stream->moveToThread(leddarThread);
    connect(this, SIGNAL(startStream()), stream, SLOT(StartStream()));
    connect(this, SIGNAL(stopStream()), stream, SLOT(StopStream()));
    connect(this, SIGNAL(startRead(QString)), stream, SLOT(StartReplay(QString)));
    connect(this, SIGNAL(stopRead()), stream, SLOT(StopReplay()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    SLOT(catchDataPoints(int,vector<float>)),
                    Qt::QueuedConnection);

    // We then connect the leddar stream and the object detector so that
    // an object is detected when new leddar data is found.
    // We also connect the object detector to the main thread to display
    // whenever an object is detected.
    this->objdetector->moveToThread(objdetectThread);
    connect(this, SIGNAL(stopDetect()), objdetector, SLOT(StopDetect()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    objdetector,
                    SLOT(StartDetect(int, vector<float>)),
                    Qt::QueuedConnection);
    connect(objdetector, SIGNAL(sendObjectDetected(string)),
                    this,
                    SLOT(catchObjectDetected(string)),
                    Qt::QueuedConnection);

    // Start the threads.
    captureThread->start();
    leddarThread->start();
    objdetectThread->start();
}

/*********************************************************************
 * The usual destructor.
***/
MainWindow::~MainWindow()
{
    delete ui;
}

/*********************************************************************
 * Function to run when the readDataButton is clicked.
 *
 * Opens a gui file dialog to allow the user to read in leddar data from
 * a file.  We then begin the threads to stream the read data and detect
 * any objects found.
 *
 * If data is already streaming, this button does nothing.
***/
void MainWindow::on_readDataButton_clicked()
{
    if (!this->stream->isrunning) {
        QString filename = QFileDialog::getOpenFileName(this, tr("Select Leddar File"),
                                                        "../LeddarData", tr("Leddar files (*.ltl)"));
        // Given a filename, find the matching recording if there exists one

        emit startRead(filename);
        emit startDetect();
    }
}

/*********************************************************************
 * Function to run when the streamButton is clicked.
 *
 * We begin the threads to start webcam capture, stream in live data,
 * and detect any objects found.
 *
 * If data is already streaming, this button does nothing.
***/
void MainWindow::on_streamButton_clicked()
{
    if (!this->stream->isrunning) {
        emit startCapture();
        emit startStream();
        emit startDetect();
    }
}

/*********************************************************************
 * Additional function for the readDataButton.
 *
 * Required; won't go away.
***/
void MainWindow::on_readDataButton_clicked(bool checked)
{
    if(checked) {
        // do nothing
    }
}

/*********************************************************************
 * Slot to catch leddar data.
 *
 * We catch the 'index' number of the data and the 'float' 'vector'
 * of 'dataPoints' emmitted.  We then display these data points as
 * Window 'labels'.
***/
void MainWindow::catchDataPoints(int index, vector<float> dataPoints) {
    QLabel* labels[] = {ui->label_1, ui->label_2,  ui->label_3,
                       ui->label_4,  ui->label_5,  ui->label_6,
                       ui->label_7,  ui->label_8,  ui->label_9,
                       ui->label_10, ui->label_11, ui->label_12};

    // Update the labels with the values of the data points.
    for (int i = 0; i <= 11; i++) {
        (labels[i])->setText(QString::number(dataPoints.at(i)));
    }
}

/*********************************************************************
 * Slot to catch the object detected.
 *
 * This function displays the name of the object detected onto a
 * Window 'label', e.g. "Wall," "Stairs," etc.
***/
void MainWindow::catchObjectDetected(string objectName) {
    ui->objectLabel->setText(QString::fromStdString("Object: " + objectName));
}

/*********************************************************************
 * Slot to catch the next frame of the webcam captured.
 *
 * This function displays the next frame captured onto the Window's
 * 'cameraView' widget.
 *
 * First, the frames are taken from the video stream as OpenCV Mat images
 * and are converted to QImages.  We adjust the colors to account for
 * different formats, and then display to the widget.
***/
void MainWindow::frameCaptured(cv::Mat* frame)
{
    ui->cameraView->setPixmap(QPixmap::fromImage(QImage(frame->data, frame->cols, frame->rows, frame->step, QImage::Format_RGB888).rgbSwapped()));
}

/*********************************************************************
 * Function to run when the cancelButton is clicked.
 *
 * We stop all threads from executing processes, except the main thread.
***/
void MainWindow::on_cancelButton_clicked()
{
    emit stopCapture();
    emit stopStream();
    emit stopRead();
    emit stopDetect();
}
