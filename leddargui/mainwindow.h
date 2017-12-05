#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "leddarmain.h"
#include "capturethread.h"
#include "OLDobjdetect.h"
#include "objdetect.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_readDataButton_clicked();

    void on_readDataButton_clicked(bool checked);

    void on_resetButton_clicked();

    void catchDataPoints(int index, vector<float> dataPoints);

    void on_streamButton_clicked();

    void frameCaptured(cv::Mat* frame);

private:
    Ui::MainWindow *ui;
    QThread* leddarThread;
    LeddarStream* stream;
    QThread* captureThread;
    CaptureThread* capture;
    QThread* objdetectThread;
    objectDetector* objdetector;
};

#endif // MAINWINDOW_H
