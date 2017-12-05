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
    //QThread thread;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_readDataButton_clicked()
{
    // TODO: PASS THIS FILENAME TO THE LEDDAR THREAD
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
}

void MainWindow::on_streamButton_clicked()
{
    //Start webcam stream
    this->capture->moveToThread(captureThread);
    connect(captureThread, SIGNAL(started()), capture, SLOT(startCapture()));
    connect(capture, SIGNAL(newFrame(cv::Mat*)), this, SLOT(frameCaptured(cv::Mat*)));
    captureThread->start();

    this->stream->moveToThread(leddarThread);
    connect(leddarThread, SIGNAL(started()), stream, SLOT(StartStream()));
    connect(stream, SIGNAL(finished()), leddarThread, SLOT(quit()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    SLOT(catchDataPoints(int,vector<float>)),
                    Qt::QueuedConnection);
    leddarThread->start();

    this->objdetector->moveToThread(objdetectThread);
    //connect(objdetectThread, SIGNAL(started()), objdetector, SLOT(detectObject()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    objdetector,
                    SLOT(processDataPoints(int, vector<float>)),
                    Qt::QueuedConnection);
    connect(objdetector, SIGNAL(finished()), objdetectThread, SLOT(quit()));
    connect(objdetector, SIGNAL(sendObjectDetected(string)), this, SLOT(catchObjectDetected(string)));
    objdetectThread->start();
}

void MainWindow::on_resetButton_clicked()
{
    ui->textBrowser->setText("");
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

    // Output the data points to the text browser.
    ui->textBrowser->append(QString::number(index));

    for (unsigned int i = 0; i < dataPoints.size(); i++) {
        ui->textBrowser->append(QString::number(dataPoints.at(i)));
    }

    ui->textBrowser->append("\n");

    // Delay a little for the presentation of this program.
    QThread::msleep(100);

}

void MainWindow::catchObjectDetected(string objectName) {
    cout << "DETECTED: " << objectName << endl;
}

void MainWindow::frameCaptured(cv::Mat* frame)
{
    //Convert Mat to QImage and display to widget
    ui->cameraView->setPixmap(QPixmap::fromImage(QImage(frame->data, frame->cols, frame->rows, frame->step, QImage::Format_RGB888).rgbSwapped()));
}
