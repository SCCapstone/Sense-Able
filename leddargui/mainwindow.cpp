#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QObject>
#include <QtWidgets>

//static QThread MainWindow::myThread;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->leddarThread = new QThread();
    this->stream = new LeddarStream;
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
    connect(leddarThread, SIGNAL(started()), stream, SLOT(StartReplay(filename)));
    connect(stream, SIGNAL(finished()), leddarThread, SLOT(quit()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    SLOT(catchDataPoints(int,vector<float>)),
                    Qt::BlockingQueuedConnection);
    leddarThread->start();
}

void MainWindow::on_streamButton_clicked()
{
    this->stream->moveToThread(leddarThread);
    connect(leddarThread, SIGNAL(started()), stream, SLOT(StartStream()));
    connect(stream, SIGNAL(finished()), leddarThread, SLOT(quit()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    SLOT(catchDataPoints(int,vector<float>)),
                    Qt::BlockingQueuedConnection);
    leddarThread->start();
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
