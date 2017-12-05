#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSignalMapper>
#include "leddarmain.h"
#include "capturethread.h"
//#include "OLDobjdetect.h"
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

    void catchDataPoints(int index, vector<float> dataPoints);

    void catchObjectDetected(string objectName);

    void on_streamButton_clicked();

    void frameCaptured(cv::Mat* frame);

private:
    Ui::MainWindow *ui;
    LeddarStream* stream;
    QThread* leddarThread;
    CaptureThread* capture;
    QThread* captureThread;
    objectDetector* objdetector;
    QThread* objdetectThread;

    QSignalMapper* signalMapper;
};

#endif // MAINWINDOW_H
