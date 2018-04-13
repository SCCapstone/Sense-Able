/*********************************************************************
 * The MainWindow class for the object detection Demo program.
 *
 * Date last modified: 8 December 2017
 * Author: Kathryn Vincent, Jonathan Senn, Austin Scampini, Caleb Kisby
***/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QObject>
#include <QtWidgets>
#include <QMetaType>
#include <QCameraInfo>
#include <QFileInfo>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>



/*********************************************************************
 *********************************************************************
                           PUBLIC
 *********************************************************************
**********************************************************************/



/*********************************************************************
 * The usual constructor.
 *
 * This constructor creates a new QWidget Window (inherits from QWidget),
 * We associate threads for each possible action that might be done
 * within this window.  In particular, we have a 'stream' and corresponding
 * 'leddarThread' for reading Leddar data from a LIDAR or file, a
 *  'capture' and corresponding 'captureThread' for capturing webcam data,
 * and finally an 'objdetector' and corresponding 'objdetectThread' for
 * detecting an object whenever new data is found.
***/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Index starts on the Landing page
    ui->stackedWidget->setCurrentIndex(1);
    //Set distance slider default. The value is divided
    //by 2 to get fractions of meters from 1.0m to 50.0m.
    ui->notificationDistanceSlider->setValue(50.0);

    this->leddarThread = new QThread();
    this->stream = new LeddarStream;
    this->captureThread = new QThread();
    this->capture = new CaptureThread();

    this->objdetectThread = new QThread();
    this->objdetector = new objectDetector();

    this->notifier = UserNotifier();


//    this->signalMapper = new QSignalMapper(this);

    // We connect the threads together via their signals and slots.

    // First, we connect the captureThread and the main thread
    // in order to display a video feed on the window.
    qRegisterMetaType<vector<string> >("vector<string>");

    this->capture->moveToThread(captureThread);
    connect(this, SIGNAL(StartCapture(string)), capture, SLOT(StartCapture(string)));
    connect(this, SIGNAL(StartVideoRecord(string,string)), capture, SLOT(StartRecord(string,string)));
    connect(this, SIGNAL(StopCapture()), capture, SLOT(StopCapture()));
    connect(capture, SIGNAL(emitFrame(cv::Mat*)), this, SLOT(frameCaptured(cv::Mat*)));

    // We then connect the leddar stream and main thread to allow the
    // window to display the data read in from the stream.
    this->stream->moveToThread(leddarThread);
    connect(this, SIGNAL(startStream()), stream, SLOT(StartStream()));
    connect(this, SIGNAL(stopStream()), stream, SLOT(StopStream()));
    connect(this, SIGNAL(startRead(string)), stream, SLOT(StartReplay(string)));
    connect(this, SIGNAL(stopRead()), stream, SLOT(StopStream()));
    connect(this, SIGNAL(emitStartLeddarRecord(string)), stream, SLOT(StartRecord(string)));
    connect(this, SIGNAL(setLeddarOrientation(bool)), stream, SLOT(setOrientation(bool)));


    connect(stream, SIGNAL(sendDataPoints(int,vector<float>, bool)),
                    SLOT(catchDataPoints(int,vector<float>, bool)),
                    Qt::QueuedConnection);
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>, bool)),
                    objdetector, SLOT(StartDetect(int, vector<float>, bool)),
                    Qt::QueuedConnection);
    connect(stream, SIGNAL(sendDataPoints(int,vector<float>, bool)),
                    capture, SLOT(catchDetections(int,vector<float>,bool)),
                    Qt::QueuedConnection);

    // We then connect the leddar stream and the object detector so that
    // an object is detected when new leddar data is found.
    // We also connect the object detector to the main thread to display
    // whenever an object is detected.
    this->objdetector->moveToThread(objdetectThread);
    connect(this, SIGNAL(stopDetect()), objdetector, SLOT(StopDetect()));
    connect(this, SIGNAL(setSigDist(float)), objdetector, SLOT(SetSignalDist(float)));
    connect(ui->QuitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

//    connect(this, SIGNAL(passNotifier(vector<string>)),
//                    objdetector, SLOT(getCurrentNotifier(vector<string>)),
//                    Qt::QueuedConnection);
    connect(objdetector, SIGNAL(emitDetectedObject(int)),
                    this, SLOT(catchDetectedObject(int)),
                    Qt::QueuedConnection);




    // Start the threads.
    captureThread->start();
    leddarThread->start();
    objdetectThread->start();

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras)
        this->cameraFileNames.push_back(cameraInfo.deviceName().toStdString());

    //This pushes all of the cameras that are available to the comobo box and lists them as
    //camera 1, camera 2, camera 3 ... etc and gives the data of each index the value of the
    //camera as it was found (e.g. "/dev/video0/" or "/dev/video1")
    int count = 1;
    foreach (const QCameraInfo &cameraInfo, cameras) {
        QString cameraValue = QString::fromStdString(cameraInfo.deviceName().toStdString());
        cout << cameraInfo.deviceName().toStdString();
        QString cameraNumber = "Camera " + QString::number(count);
        ui->cameraComboBox->addItem(cameraNumber, cameraValue);
        count++;
    }

    // UI
    ui->beepCheckBox->setChecked(true);
    // Set viewport to default image
    ui->cameraView->setPixmap(QPixmap::fromImage(Mat2QImage(&capture->defaultImage)));

}


/*********************************************************************
 * The usual destructor.
***/
MainWindow::~MainWindow()
{
    delete ui;
}


/*********************************************************************
 *********************************************************************
                        Helper Functions
 *********************************************************************
**********************************************************************/
//These functions aren't defined in the header, however they are crucial
//to the running of this code


/*********************************************************************
 * Stops all threads
***/
void MainWindow::stopAll()
{
    emit StopCapture();
    emit stopStream();
    emit stopRead();
    emit stopDetect();
    QThread::usleep(.35);
}


/*********************************************************************
 * Takes a *.ltl file and returns a the same basename with a .mp4
 *  extension
***/
string MainWindow::ltlToAVI(string leddarFile)
{
    QFileInfo file(QString::fromStdString(leddarFile));
    return (file.absolutePath() +"/"+ file.baseName() + ".avi").toStdString();
}


/*********************************************************************
 * Converts opencv Mat to QImage
***/
QImage MainWindow::Mat2QImage(cv::Mat* img)
{
    return QImage(
                img->data, img->cols, img->rows,
                img->step, QImage::Format_RGB888).rgbSwapped();
}


/*********************************************************************
 * Changes the UserNotifier sound Mapping according to the ui
 *
 *
 * This is pretty hacky. Two facts
 *     1: The ui->objX corresponds to an object as defined in globalconstants.h
 *         obj1 = WALL, obj2 = WALL_CORNER, etc/
 *     2: The currentIndex() of the choice corresponds to the index of of a sound
 *        file in the defaultSoundFiles vector.
 *
 * So, we map the index of the choice of an objX to the value of the defaulSoundFiles
 * vector.
***/
void MainWindow::updateSoundFiles()
{
    if (ui->beepCheckBox->isChecked() ) {
        notifier.fileType = SOUNDFILES;
    }
    else { // if (ui->speechCheckBox->isChecked())
        notifier.fileType = VOICEFILES;
    }

    // Grab the selected object -> sound associations
    vector<int> newSoundFiles = {
        ui->obj1_notif_choice->currentIndex(), ui->obj2_notif_choice->currentIndex(),
        ui->obj3_notif_choice->currentIndex(), ui->obj4_notif_choice->currentIndex(),
        ui->obj5_notif_choice->currentIndex(), ui->obj6_notif_choice->currentIndex(),
        ui->obj7_notif_choice->currentIndex(), ui->obj8_notif_choice->currentIndex()
    };

    // TODO:: Explain this code
    for (unsigned int i=0; i < newSoundFiles.size(); i++) {
        notifier.soundFiles.at(i) = notifier.defaultSoundFiles.at(newSoundFiles.at(i));
    }

}


/*********************************************************************
 * Returns the time since epoch in milliseconds
 */
//
long MainWindow::getCurrentTime()
{
    long ms = chrono::duration_cast< chrono::milliseconds> (
                chrono::system_clock::now().time_since_epoch()).count();
    return ms;
}



/*********************************************************************
 *********************************************************************
                           PRIVATE
 *********************************************************************
**********************************************************************/


/*********************************************************************
 * Slot to catch leddar data.
 *
 * We catch the 'index' number of the data and the 'float' 'vector'
 * of 'dataPoints' emmitted.  We then display these data points as
 * Window 'labels'.
***/
void MainWindow::catchDataPoints(int index, vector<float> dataPoints, bool aOrientation) {
    QLabel* labels[] = {ui->pt1, ui->pt2,  ui->pt3,
                       ui->pt4,  ui->pt5,  ui->pt6,
                       ui->pt7,  ui->pt8,  ui->pt9,
                       ui->pt10, ui->pt11, ui->pt12,
                       ui->pt13, ui->pt14, ui->pt15,
                       ui->pt16};

    // Update the labels with the values of the data points.
    for (int i = 0; i <= 15; i++) {
        (labels[i])->setText(QString::number(dataPoints.at(i)).mid(0, 4));
    }
}


/*********************************************************************
 * Slot to catch the object detected.
 *
 * This function displays the name of the object detected onto a
 * Window 'label', e.g. "Wall," "Stairs," etc.
***/
void MainWindow::catchDetectedObject(int object) {
    cout << "MainWindow::catchDetectedObject -> Object Detected: " << object << endl;
    string objectName = "None";

    if ( object != NONE ) {

        // Look up object name
        objectName = OBJECT_MAP[object];

        if ( getCurrentTime() - lastNotification > 1000 ){
            lastNotification = getCurrentTime();
            // Play Sound
            notifier.playSound(object);
        }

    }

    ui->objectLabel->setText(QString::fromStdString("Object: " + objectName));
}


/*********************************************************************
 * Slot to catch the next frame of the webcam captured.
 *
 * This function displays the next frame captured onto the Window's
 * 'cameraView' widget.
 *
 * First, the frames are taken from the video stream as OpenCV Mat images
 * and are converted to QImages.  We adjust the colors to account for
 * different formats, and then display to the widget.
***/
void MainWindow::frameCaptured(cv::Mat* frame)
{
    // TODO: IS THIS REALLY SLOW? IT SEEM LIKE THIS WOULD BE SLOW
    QPixmap resize = QPixmap::fromImage(
                QImage(
                    frame->data, frame->cols, frame->rows,
                    frame->step, QImage::Format_RGB888).rgbSwapped()
                );
    ui->cameraView->setPixmap(resize.scaled(ui->cameraView->size(), Qt::KeepAspectRatio));
}


/*********************************************************************
 *********************************************************************
                       Button/GUI functions
 *********************************************************************
 *********************************************************************/



/*********************************************************************
 *                      Home Page Buttons                            *
 *********************************************************************/



/*********************************************************************
 * Function to run when the streamButton is clicked.
 *
 * Navigates to the Stream Page from the Home Page.
***/
void MainWindow::on_streamButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    emit clickedButton();

    this->updateSoundFiles();

}


/*********************************************************************
 * Function to run when the streamPageButton is clicked.
 *
 * Navigates to the Settings Page from the Home Page.
***/
void MainWindow::on_settingsPageButton_clicked()
{
    emit clickedButton();
    //if no notification was checked then default to beep notifiers
    if((ui->speechCheckBox->isChecked() == false) && (ui->beepCheckBox->isChecked() == false)) {
        ui->beepCheckBox->setChecked(true);
    }
    ui->stackedWidget->setCurrentIndex(2);

}


/*********************************************************************
 * Function to run when the QuitButton is clicked.
 *
 * Emits a signal that closes out of the application.
***/
void MainWindow::on_QuitButton_clicked()
{
    emit clickedButton();
}



/*********************************************************************
 *                     Stream/Go Page Buttons                        *
 *********************************************************************/



/*********************************************************************
 * Function to run when the back Button on the go page is clicked.
 *
 * We stop all threads from executing processes, except the main thread.
 * and then we go back to the main page of the app
***/
void MainWindow::on_backButtonGo_clicked()
{
    stopAll();
    ui->stackedWidget->setCurrentIndex(1);
}


/*********************************************************************
 * Function to run when the Stream From Device Button is clicked.
 *
 * We begin the threads to start webcam capture, stream in live data,
 * and detect any objects found.
 *
 * If data is already streaming, this button does nothing.
***/
void MainWindow::on_go_StreamFromDevice_button_clicked()
{
    //Testing signal
    emit streamButtonClicked();

    if (!this->stream->isrunning && this->stream->isstopped) {
        updateSoundFiles();

        emit StartCapture(videoStream);
        emit startStream();
    }
}


/*********************************************************************
 * Function to run when the Read From File button is clicked.
 *
 * Opens a gui file dialog to allow the user to read in leddar data from
 * a file.  We then begin the threads to stream the read data and detect
 * any objects found.
 *
 * If data is already streaming, this button does nothing.
***/
void MainWindow::on_go_ReadFromFile_button_clicked()
{

    if (!this->stream->isrunning) {

        string leddarFileName = QFileDialog::getOpenFileName(this, tr("Select Leddar File"),
                                                        "../LeddarData", tr("Leddar files (*.ltl)")).toStdString();
        string videoFilename = ltlToAVI(leddarFileName);

        cout << "Reading Leddar File: " << leddarFileName << endl;
        cout << "Readnig Video File: " << videoFilename << endl;

        this->updateSoundFiles();

        // Given a filename, find the matching recording if there exists one start replay
        QFileInfo check_file(QString::fromStdString(videoFilename));
        if (check_file.exists() && check_file.isFile())
        {
            emit StartCapture(videoFilename);

        }
        emit startRead(leddarFileName);
    }
}


/*********************************************************************
 * Function to run when the Record button is clicked.
 *
 * Opens a gui file dialog to allow the user to create a name in leddar
 * data for a file.  We then begin to save the leddar data produced as
 * well as record video of the webcam as it should be lined up with the
 * sensor.
 *
***/
void MainWindow::on_go_Record_button_clicked()
{
    emit clickedButton();
    // Check that stream is stopped
    if (!stream->isrunning && stream->isstopped) {

        // Open File dialog, get save name
        QFileDialog dialog;
        string leddarFileName = dialog.getSaveFileName(NULL,
                                                 "Select or Create a new save file",
                                                 "../LeddarData/",
                                                 "Leddar Files (*.ltl)").toStdString();

        // User exited file dialog. No File selected
        if (leddarFileName.length() == 0 ) {
            return;
        }


        // Check that the Leddar filename is valid
        QFileInfo file(QString::fromStdString(leddarFileName));

        // If no prefix, add one
        if ( file.suffix().isEmpty() ) {
            leddarFileName += ".ltl";
        }
        // Any other extension is invalid
        else if ( file.completeSuffix() != "ltl") {
            QMessageBox::information(this, tr("Invalid Extension"),
                                     tr("Invalid file extension specified! .ltl files only!"));
            cout << "File Extension should be .ltl!" << endl;
            return;
        }

        // Video file has identical path, but different extension
        string videoFileName = ltlToAVI(leddarFileName);

        cout << "\nLeddar File Name: " << leddarFileName << endl;
        cout << "Video Filename: " <<  videoFileName << endl;



        this->updateSoundFiles();

        emit StartVideoRecord(videoStream, videoFileName);
        emit emitStartLeddarRecord(leddarFileName);

    } // if (!stream->isrunning && stream->isstopped) {
}


/*********************************************************************
 * Function to run when the Stop Button on the go page is clicked.
 *
 * We stop all threads from executing processes, except the main thread.
 *
***/
void MainWindow::on_go_StopAll_button_clicked()
{
    emit clickedButton();
    stopAll();
}


/*********************************************************************
 * Function to run when the Change Orientation Button on the go page
 * is clicked.
 *
 *
***/
void MainWindow::on_changeOrient_clicked()
{
//    bool was_playing = stream->isrunning;
//    bool was_recording = capture->isvideoWriter;
//    bool was_replay = stream->isReplay;
//    stopAll();

    leddarOrientation = !leddarOrientation;

    if (leddarOrientation == VERTICAL) {
       ui->orientLabel->setText("Orientation: Vertical");
    }
    else { // HORIZONTAL
        ui->orientLabel->setText("Orientation: Horizontal");
    }

    emit setLeddarOrientation(leddarOrientation);

    QThread::usleep(.15);

    // We cant stop then start a recording or reading from a file
//    if (was_playing && !was_recording && !was_replay) {
//       emit startCapture(cameraNumber);
//       emit startStream();
//       emit passNotifier(this->notifier.soundFiles);
//    }
}


/*********************************************************************
 * Function to run when the Camera ComboBox index changes on the go page
 *
 * This changes the web-camera to that of the webcam indexed at the selected
 * spot in the combo box. We stop the threads when a camera is chosen and then
 * restart them.
 *
***/
void MainWindow::on_cameraComboBox_currentIndexChanged(int index)
{
    emit clickedButton();

    bool was_playing = this->stream->isrunning;
    bool was_recording = this->capture->isRecording;
    QString currentCamera = ui->cameraComboBox->currentData().toString();

    // We cant change the video stream input of a recorded file,
    // so don't stop stream.
    if ( !stream->isReplay ) {
        stopAll();
    }

    videoStream = currentCamera.toStdString();

    // We cant stop and then restart while recording
    if (was_playing && !was_recording) {
        QThread::usleep(.15);
       emit StartCapture(videoStream);
       emit startStream();
    }
}



/*********************************************************************
 *                     Settings Page Buttons                         *
 *********************************************************************/



/*********************************************************************
 * Function to run when the Back Button on the Settings Page
 * is clicked.
 *
 * Navigates you back to the home page
 *
***/
void MainWindow::on_backButtonSettings_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


/*********************************************************************
 * Function to run when the Distance Slider is changed to a new value.
 *
 * Takes the value input by the user and displays it in meters or feet
 * depending on the units setting.
 * The function will then convert the value to meters if it is in feet
 * and emit a signal to set sig_dist to the new value.
***/
void MainWindow::on_notificationDistanceSlider_valueChanged(int value)
{
    if(value<=0) value = 1;
    QString displayDist;
    float metricDistance;
    if(metricUnits){
        metricDistance = value/2.0;
        displayDist = QString::number(metricDistance);
        ui->notifDistanceLabel->setText(displayDist + " m");
    }
    else if(!metricUnits) {
        displayDist = QString::number((value), 'f', 0);
        ui->notifDistanceLabel->setText(displayDist + " ft");
        metricDistance = value*0.3048;
    }
    //qDebug() << "Metric value passed to sigDist: " << metricDistance;
    emit setSigDist(metricDistance);
}


/*********************************************************************
 * Function to run when the state of the Speech CheckBox on the
 * settings page is changed.
 *
***/
void MainWindow::on_speechCheckBox_stateChanged()
{
    //if the beep checkbox is changed then uncheck it
    if(ui->beepCheckBox->isChecked()) {
        ui->beepCheckBox->setChecked(false);
    }
}


/*********************************************************************
 * Function to run when the state of the Beep CheckBox on the Settings
 * page is changed.
 *
***/
void MainWindow::on_beepCheckBox_stateChanged()
{
    //if the speech checkbox is changed then uncheck it
    if(ui->speechCheckBox->isChecked()) {
        ui->speechCheckBox->setChecked(false);
    }
}


/*********************************************************************
 * Function to run when the index of the ComboBox on the Settings page
 * is changed.
 *
 * Converts the distance displayed on screen from metric to US customs
 * measurements.
 *
***/
void MainWindow::on_settingsComboBox_currentIndexChanged(int index)
{
    //feet to meters
    if(index==0){
        metricUnits = true;
        int newValue = ui->notificationDistanceSlider->value()*.3048*2;
        //Setting the range to 1-100 and dividing by 2 to in order to get .5 meter intervals
        ui->notificationDistanceSlider->setRange(1, 100);
        emit ui->notificationDistanceSlider->valueChanged(newValue);
        ui->notificationDistanceSlider->setSliderPosition(newValue);
    }
    //meters to feet
    else if(index==1){
        metricUnits = false;
        //Setting maximum to 164 feet to keep similar range as meters
        ui->notificationDistanceSlider->setRange(1, 164);
        int newValue = ui->notificationDistanceSlider->value()/(.3048*2);
        emit ui->notificationDistanceSlider->valueChanged(newValue);
        ui->notificationDistanceSlider->setSliderPosition(newValue);
    }

}


/*********************************************************************
 * Function to run when the Notifications Button on the Settings Page
 * is clicked.
 *
 * Navigates you to the Notifications page
 *
***/
void MainWindow::on_notificationsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


/*********************************************************************
 * Function to run when the Back Button on the Notifications Page
 * is clicked.
 *
 * Navigates you back to the home page
 *
***/
void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}


// End of file mainwindow.cpp

