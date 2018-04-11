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

private slots:
    //void on_readDataButton_clicked();

    //void on_readDataButton_clicked(bool checked);

    void catchDataPoints(int index, vector<float> dataPoints, bool aOrientation);

    void catchDetectedObject(int object);

    void on_streamButton_clicked();

    void frameCaptured(cv::Mat* frame);

    //void on_cancelButtonRead_clicked();

    void on_settingsPageButton_clicked();

    void on_actionMain_Menu_triggered();

    void on_notificationsButton_clicked();

    //void on_readDataPageButton_clicked();

    void on_backButton_clicked();

    void on_backButtonGo_clicked();

    void on_backButtonSettings_clicked();

    //void on_backButtonRead_clicked();

   // void on_changeCamera_clicked();

    void on_changeOrient_clicked();

    void on_QuitButton_clicked();

    void on_notificationDistanceSlider_valueChanged(int value);

    void on_speechCheckBox_stateChanged();

    void on_beepCheckBox_stateChanged();

    void on_go_ReadFromFile_button_clicked();

    void on_go_StreamFromDevice_button_clicked();

    void on_go_Record_button_clicked();

    void on_go_StopAll_button_clicked();

    void on_cameraComboBox_currentIndexChanged(int index);

signals:
    // Signals to capturethread.cpp
    void startCapture(string);
    void emitStartVideoRecord(string, string);
    void stopCapture();

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

    // Signals to Usernotifier
    void passNotifier(vector<string>); // Deprecrated?

    void clicked(); // deprecated?

    //used for behavioral tests
    void streamButtonClicked();

private:
    Ui::MainWindow *ui;
    LeddarStream* stream;
    QThread* leddarThread;
    CaptureThread* capture;
    QThread* captureThread;
    objectDetector* objdetector;
    QThread* objdetectThread;

    vector<string> cameraFileNames;
    //TODO: FIND A BETTER DEFAULT
    string videoStream = "/dev/video0";
    int leddarOrientation = true;

    QSignalMapper* signalMapper;
    UserNotifier notifier;
    vector<string> defaultSoundOrder;

    //Helper functions
    void stopAll();
    void updateSoundFiles();
    string ltlToAVI(string leddarFile);
};

#endif // MAINWINDOW_H
