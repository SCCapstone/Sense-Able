#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include "opencv2/imgcodecs.hpp"
#include "mattoqimage.h"
#include "opencv2/imgproc/imgproc.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImg()
{
    //open image from file
    fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),QDir::currentPath(),tr("Image Files [ *.jpg , *.jpeg , *.bmp , *.png , *.gif]"));
    charFileName = fileName.toLocal8Bit().data();
    matImg = cv::imread(charFileName);
    //qimgNew = MatToQImage(matImg);
    //ui->label->setPixmap(QPixmap::fromImage(qimgNew));
    ui->label->setPixmap(QPixmap::fromImage(QImage(matImg.data, matImg.cols, matImg.rows, matImg.step, QImage::Format_RGB888).rgbSwapped()));
    //check if valid pathname
    if (!matImg.empty())
    {
        ui->label_2->setText(charFileName);
    }
}

void MainWindow::on_pushButton_clicked()
{
    openImg();
}

void MainWindow::on_pushButton_2_clicked()
{
    //flip horizontally
    cv::flip(matImg,matImg,1);
    //converts openCV Mat type to QImage for display
    qimgNew = MatToQImage(matImg);
    ui->label->setPixmap(QPixmap::fromImage(qimgNew));
}

void MainWindow::on_pushButton_3_clicked()
{
    //greyscale
    if(!matImg.empty()){
        Mat temp;
        cv::cvtColor(matImg,temp,CV_RGB2GRAY);
        qimgNew = MatToQImage(temp);
        ui->label->setPixmap(QPixmap::fromImage(qimgNew));
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    //flip vertically
    cv::flip(matImg,matImg,0);
    ui->label->setPixmap(QPixmap::fromImage(QImage(matImg.data, matImg.cols, matImg.rows, matImg.step, QImage::Format_RGB888).rgbSwapped()));
}

void MainWindow::on_pushButton_5_clicked()
{
    //edge detection
    if(!matImg.empty()){
        Mat temp;
        cv::Canny(matImg, temp, 50, 100, 3, 0);
        qimgNew = MatToQImage(temp);
        ui->label->setPixmap(QPixmap::fromImage(qimgNew));
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    //reset image
    if (matImg.empty())
    {
        ui->label_2->setText("no image");
        openImg();
    }
    else {
        matImg = imread(charFileName);
        qimgNew = MatToQImage(matImg);
        ui->label->setPixmap(QPixmap::fromImage(qimgNew));
    }
}
