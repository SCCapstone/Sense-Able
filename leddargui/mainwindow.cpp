#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QObject>
#include <QtWidgets>
#include <QMetaType>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

//static QThread MainWindow::myThread;

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

    // Connect the threads, signals, and slots together.
    this->capture->moveToThread(captureThread);
    connect(this, SIGNAL(startCapture()), capture, SLOT(StartCapture())); /***************************************/
    connect(this, SIGNAL(stopCapture()), capture, SLOT(StopCapture()));
    connect(capture, SIGNAL(newFrame(cv::Mat*)), this, SLOT(frameCaptured(cv::Mat*)));

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

void MainWindow::on_readDataButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select Leddar File"),
                                                    "./LeddarData", tr("Leddar files (*.ltl)"));
    // Given a filename, find the matching recording if there exists one

    emit startRead(filename);
    emit startDetect();

/*    // TODO: PASS THIS FILENAME TO THE LEDDAR THREAD
    QString filename = QFileDialog::getOpenFileName(this, tr("Select Leddar File"),
                                                    "../LeddarData", tr("Leddar files (*.ltl)"));
    qInfo() << filename;
    // Given a filename, find the matching recording if there exists one
    this->stream->moveToThread(leddarThread);

    // Roundabout "magical" way to pass 'filename' to 'StartReplay'.
    connect(leddarThread, SIGNAL(started()), signalMapper, SLOT(map()));
    signalMapper->setMapping(leddarThread, filename);
    connect(signalMapper, SIGNAL(mapped(QString)), stream, SLOT(StartReplay(QString)));

    //connect(leddarThread, SIGNAL(started()), stream, SLOT(StartReplay(filename)));
    connect(stream, SIGNAL(finished()), leddarThread, SLOT(quit()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    SLOT(catchDataPoints(int,vector<float>)),
                    Qt::BlockingQueuedConnection);
    leddarThread->start();

    this->objdetector->moveToThread(objdetectThread);
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    objdetector,
                    SLOT(processDataPoints(int, vector<float>)),
                    Qt::QueuedConnection);
    connect(objdetector, SIGNAL(finished()), objdetectThread, SLOT(quit()));
    connect(objdetector, SIGNAL(sendObjectDetected(string)),
                         SLOT(catchObjectDetected(string)),
                         Qt::QueuedConnection);
    objdetectThread->start();*/
}

void MainWindow::on_streamButton_clicked()
{
    emit startCapture();
    emit startStream();
    emit startDetect();
}

void MainWindow::on_readDataButton_clicked(bool checked)
{
    if(checked) {
        // do nothing
    }
}

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

void MainWindow::catchObjectDetected(string objectName) {
    ui->objectLabel->setText(QString::fromStdString("Object: " + objectName));
}

void MainWindow::frameCaptured(cv::Mat* frame)
{
    //Convert Mat to QImage and display to widget
    ui->cameraView->setPixmap(QPixmap::fromImage(QImage(frame->data, frame->cols, frame->rows, frame->step, QImage::Format_RGB888).rgbSwapped()));
}

void MainWindow::on_cancelButton_clicked()
{
    emit stopCapture();
    emit stopStream();
    emit stopRead();
    emit stopDetect();
}
