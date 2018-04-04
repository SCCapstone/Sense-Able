#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSignalMapper>
#include "leddarthread.h"
#include "capturethread.h"
//#include "OLDobjdetect.h"
#include "objectdetectthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void stopAll();

private slots:
    void on_readDataButton_clicked();

    void on_readDataButton_clicked(bool checked);

    void catchDataPoints(int index, vector<float> dataPoints, bool aOrientation);

    void catchObjectDetected(string objectName);

    void on_streamButton_clicked();

    void frameCaptured(cv::Mat* frame);

    void on_cancelButtonRead_clicked();

    void on_settingsPageButton_clicked();

    void on_actionMain_Menu_triggered();

    void on_notificationsButton_clicked();

    void on_readDataPageButton_clicked();

    void on_backButton_clicked();

    void on_backButtonGo_clicked();

    void on_backButtonSettings_clicked();

    void on_backButtonRead_clicked();

    void on_changeCamera_clicked();

    void on_changeOrient_clicked();

    void on_QuitButton_clicked();

    void on_Play_clicked();

    void on_notificationDistanceSlider_valueChanged(int value);

signals:
    void startCapture(int);
    void stopCapture();
    void startStream();
    void stopStream();
    void startRead(QString);
    void stopRead();
    void startDetect();
    void stopDetect();
    void clicked();

    void streamButtonClicked();
    void passNotifier(vector<string>);
    void setSigDist(float);
    void setLeddarOrientation(bool);

private:
    Ui::MainWindow *ui;
    LeddarStream* stream;
    QThread* leddarThread;
    CaptureThread* capture;
    QThread* captureThread;
    objectDetector* objdetector;
    QThread* objdetectThread;

    vector<string> cameraFileNames;
    int cameraNumber = 0;
    int leddarOrientation = true;

    QSignalMapper* signalMapper;
    UserNotifier notifier;
    vector<string> defaultSoundOrder;
};

#endif // MAINWINDOW_H
