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
    void on_readDataButton_clicked();

    void on_readDataButton_clicked(bool checked);

    void catchDataPoints(int index, vector<float> dataPoints);

    void catchObjectDetected(string objectName);

    void on_streamButton_clicked();

    void frameCaptured(cv::Mat* frame);

    void on_cancelButton_clicked();

    void on_cancelButtonRead_clicked();

    void on_settingsPageButton_clicked();

    void on_actionMain_Menu_triggered();

    void on_calibratePageButton_clicked();

    void on_notificationsButton_clicked();

    void on_readDataPageButton_clicked();

    void on_backButton_clicked();

    void on_backButtonGo_clicked();

    void on_backButtonSettings_clicked();

    void on_backButtonRead_clicked();

    void on_backButtonCalibration_clicked();

    void on_page_2_customContextMenuRequested(const QPoint &pos);

signals:
    void startCapture();
    void stopCapture();
    void startStream();
    void stopStream();
    void startRead(QString);
    void stopRead();
    void startDetect();
    void stopDetect();

    void streamButtonClicked();

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
