#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSignalMapper>
#include "leddarthread.h"
#include "capturethread.h"
//#include "OLDobjdetect.h"
#include "objectdetectthread.h"
#include <chrono>

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

    void catchDataPoints(int index, vector<float> dataPoints, bool aOrientation);
    void catchDetectedObject(int object);
    void frameCaptured(cv::Mat* frame);

    /**************************************************************************
     *                         Button/GUI functions                           *
     **************************************************************************/

    //Home Page Buttons
    void on_streamButton_clicked();
    void on_settingsPageButton_clicked();
    void on_QuitButton_clicked();

    //Stream/Go Page GUI
    void on_backButtonGo_clicked();
    void on_go_StreamFromDevice_button_clicked();
    void on_go_ReadFromFile_button_clicked();
    void on_go_Record_button_clicked();
    void on_go_StopAll_button_clicked();
    void on_changeOrient_clicked();
    void on_cameraComboBox_currentIndexChanged(int index);

    //Setting Page
    void on_backButtonSettings_clicked();
    void on_notificationDistanceSlider_valueChanged(int value);
    void on_speechCheckBox_stateChanged();
    void on_beepCheckBox_stateChanged();
    void on_settingsComboBox_currentIndexChanged(int index);
    void on_notificationsButton_clicked();

    //Notifications Page
     void on_backButton_clicked();


signals:
    // Signals to capturethread.cpp
    void StartCapture(string);
    void StartVideoRecord(string, string);
    void StopCapture();

    // Signals to leddarthread.cpp
    void startStream();
    void stopStream();
    void startRead(string);
    void stopRead(); // Deprecated?
    void emitStartLeddarRecord(string);
    void setLeddarOrientation(bool);

    // Signals to ObjectDetect
    void startDetect(); // Deprecated?
    void stopDetect();  // Deprecated?
    void setSigDist(float);


//<<<<<<< HEAD
//    void clicked();

//    //used for behavioral tests
//=======
    // Used for behavioral tests
    void clickedButton();
    void streamButtonClicked();

private:
    Ui::MainWindow *ui;
    LeddarStream* stream;
    QThread* leddarThread;
    CaptureThread* capture;
    QThread* captureThread;
    objectDetector* objdetector;
    QThread* objdetectThread;

    long lastNotification = 0;

    vector<string> cameraFileNames;
    //TODO: FIND A BETTER DEFAULT
    string videoStream = "/dev/video0";
    int leddarOrientation = true;
    bool metricUnits = true;

    QSignalMapper* signalMapper;
    UserNotifier notifier;
    vector<string> defaultSoundOrder;

    //Helper functions
    void stopAll();
    void updateSoundFiles();
    long getCurrentTime();
    string ltlToAVI(string leddarFile);
    QImage Mat2QImage(cv::Mat* img);
};

#endif // MAINWINDOW_H
