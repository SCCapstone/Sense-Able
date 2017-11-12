#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "leddarmain.h"
#include "leddarmain.cpp"
#include <QCoreApplication>
#include <QThread>
#include <QObject>

//static QThread MainWindow::myThread;

void Worker::runLeddarMain() {
    leddarmain(0, nullptr);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread* thread = new QThread();
    //QThread thread;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_readDataButton_clicked()
{
    QThread myThread;
    Worker *worker = new Worker;
    worker->moveToThread(&myThread);
    connect(&myThread, SIGNAL(started()), worker, SLOT(runLeddarMain()));
    myThread.start();

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


