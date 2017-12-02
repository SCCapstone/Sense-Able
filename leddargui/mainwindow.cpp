#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QObject>

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
    this->stream->moveToThread(leddarThread);
    connect(leddarThread, SIGNAL(started()), stream, SLOT(leddarmain()));
    connect(stream, SIGNAL(finished()), leddarThread, SLOT(quit()));
//    connect(stream, SIGNAL(sendDataPoints()), this, SLOT(catchDataPoints()));
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>)),
                    SLOT(catchDataPoints(int,vector<float>)),
                    Qt::BlockingQueuedConnection);
    leddarThread->start();

    //QThread thread;
    ui->textBrowser->setText("Read in data here probably");
    //MainWindow::moveToThread(thread);
    //MainWindow::connect(&thread, SIGNAL(started()), this, SLOT(leddarmain()));
    //thread.start();
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
    ui->textBrowser->setText("TEST");
    ui->textBrowser->setText(QString::number(index));
}
