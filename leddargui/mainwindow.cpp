#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QObject>
#include <QtWidgets>
#include <QMetaType>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

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

    this->signalMapper = new QSignalMapper(this);

    /*
     * Connect the threads, signals, and slots together.
     * This section connects signals and slots between the capture thread and the main thread
     * in order to display a video feed.
     */
    this->capture->moveToThread(captureThread);
    connect(this, SIGNAL(startCapture()), capture, SLOT(StartCapture())); /***************************************/
    connect(this, SIGNAL(stopCapture()), capture, SLOT(StopCapture()));
    connect(capture, SIGNAL(newFrame(cv::Mat*)), this, SLOT(frameCaptured(cv::Mat*)));

    /*
     * Connects the signals and slots between the leddar stream and main thread.
     * Used to allow the gui to display the data read in from a file or the sensor.
     */
    this->stream->moveToThread(leddarThread);
    connect(this, SIGNAL(startStream()), stream, SLOT(StartStream())); /**********************************/
    connect(this, SIGNAL(stopStream()), stream, SLOT(StopStream()));
    connect(this, SIGNAL(startRead(QString)), stream, SLOT(StartReplay(QString))); /**********************/
    connect(this, SIGNAL(stopRead()), stream, SLOT(StopReplay()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    SLOT(catchDataPoints(int,vector<float>)),
                    Qt::QueuedConnection);

    this->objdetector->moveToThread(objdetectThread);
    //connect(this, SIGNAL(startDetect()), objdetector, SLOT(StartDetect()); /***************************/
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

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Opens a file dialog to allow the user to read in data from a file and view it in the gui.
 */
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

/*
 * Starts a stream to read in data directly from the Leddar sensor.
 * Also opens the camera and begins object detection.
 */
void MainWindow::on_streamButton_clicked()
{
    if (!this->stream->isrunning) {
        emit startCapture();
        emit startStream();
        emit startDetect();
    }
}

void MainWindow::on_readDataButton_clicked(bool checked)
{
    if(checked) {
        // do nothing
    }
}

/*
 * Takes the data from the Leddar stream and updates the gui with the most recent values.
 */
void MainWindow::catchDataPoints(int index, vector<float> dataPoints) {
    QLabel* labels[] = {ui->label_1, ui->label_2,  ui->label_3,
                       ui->label_4,  ui->label_5,  ui->label_6,
                       ui->label_7,  ui->label_8,  ui->label_9,
                       ui->label_10, ui->label_11, ui->label_12};

    // Update the labels with the values of the data points.
    for (int i = 0; i <= 11; i++) {
        (labels[i])->setText(QString::number(dataPoints.at(i)));
    }

    // Delay a little for the presentation of this program.


}

/*
 * Shows the name of the object detected, i.e. "Wall", "Stairs", etc.
 */
void MainWindow::catchObjectDetected(string objectName) {
    ui->objectLabel->setText(QString::fromStdString("Object: " + objectName));
}

/*
 * Takes frames from video stream as OpenCV Mat images and converts to QImage.
 * Adjusts the colors to account for different formats and then displays to the widget.
 */
void MainWindow::frameCaptured(cv::Mat* frame)
{

    ui->cameraView->setPixmap(QPixmap::fromImage(QImage(frame->data, frame->cols, frame->rows, frame->step, QImage::Format_RGB888).rgbSwapped()));
}

void MainWindow::on_cancelButton_clicked()
{
    emit stopCapture();
    emit stopStream();
    emit stopRead();
    emit stopDetect();
}
