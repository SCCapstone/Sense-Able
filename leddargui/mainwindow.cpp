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
    //Set to start the application on the Go Page.
    //Will eventually start on the Landing Page.
    //Index has been changed so it now starts on the Landing page
    ui->stackedWidget->setCurrentIndex(1);
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
    connect(this, SIGNAL(startCapture(string)), capture, SLOT(StartCapture(string)));
    connect(this, SIGNAL(emitStartVideoRecord(string,string)), capture, SLOT(StartRecord(string,string)));
    connect(this, SIGNAL(stopCapture()), capture, SLOT(StopCapture()));
    connect(capture, SIGNAL(newFrame(cv::Mat*)), this, SLOT(frameCaptured(cv::Mat*)));

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
                    capture, SLOT(captureDataPoints(int,vector<float>,bool)),
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

    foreach (const QCameraInfo &cameraInfo, cameras)
        cout << cameraInfo.deviceName().toStdString();

    // UI
    ui->beepCheckBox->setChecked(true);

    // Hide some buttons
//    ui->orientLabel->setHidden(true);
//    ui->changeOrient->setHidden(true);
//    ui->cameraLabel->setHidden(true);
//    ui->changeCamera->setHidden(true);
}

/*********************************************************************
 * The usual destructor.
***/
MainWindow::~MainWindow()
{
    delete ui;
}

/*********************************************************************
 * Stops all threads
***/
void MainWindow::stopAll()
{
    emit stopCapture();
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
 * Function to run when the readDataButton is clicked.
 *
 * Opens a gui file dialog to allow the user to read in leddar data from
 * a file.  We then begin the threads to stream the read data and detect
 * any objects found.
 *
 * If data is already streaming, this button does nothing.
***/
void MainWindow::on_readDataButton_clicked()
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
//            emit startCapture(videoFilename);

        }
        emit startRead(leddarFileName);
    }
}

/*********************************************************************
 * Function to run when the streamButton is clicked.
 *
 * We begin the threads to start webcam capture, stream in live data,
 * and detect any objects found.
 *
 * If data is already streaming, this button does nothing.
***/
void MainWindow::on_streamButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    //emit streamButtonClicked();

    this->updateSoundFiles();

//    if (!this->stream->isrunning) {
//        emit startCapture(cameraNumber);
//        emit startStream();
//        emit passNotifier(this->notifier.soundFiles);
//        emit startDetect();  We should not start detecting until an object
//                             is actually detected.
//    }
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
    if ( ui->beepCheckBox->isChecked() ) {
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

    for (unsigned int i=0; i < newSoundFiles.size(); i++) {
        notifier.soundFiles.at(i) = notifier.defaultSoundFiles.at(newSoundFiles.at(i));
    }

}

/*********************************************************************
 * Additional function for the readDataButton.
 *
 * Required; won't go away.
***/
void MainWindow::on_readDataButton_clicked(bool checked)
{
    if(checked) {
        // do nothing
    }
}

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
        (labels[i])->setText(QString::number(dataPoints.at(i)));
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
        // Play Sound
        notifier.playSound(object);
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
//    cout << frame->empty()  << "  " << frame->cols << "  " << frame->rows;
    ui->cameraView->setPixmap(
                QPixmap::fromImage(
                    QImage(
                        frame->data, frame->cols, frame->rows,
                        frame->step, QImage::Format_RGB888).rgbSwapped()
                    )
                );
//    cout << "  >314 is not crashing" << endl;

}

/*********************************************************************
 * Function to run when the cancelButtonRead is clicked.
 *
 * We stop all threads from executing processes, except the main thread.
 * Does the same as the above button but is used for a different page of
 * the application
***/
void MainWindow::on_cancelButtonRead_clicked()
{
    stopAll();
}

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

void MainWindow::on_backButtonRead_clicked()
{
    stopAll();
    ui->stackedWidget->setCurrentIndex(1);
}

//Switching between pages
void MainWindow::on_settingsPageButton_clicked()
{
    //if no notification was checked then default to beep notifiers
    if((ui->speechCheckBox->isChecked() == false) && (ui->beepCheckBox->isChecked() == false)) {
        ui->beepCheckBox->setChecked(true);
    }
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_actionMain_Menu_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_notificationsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_readDataPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_backButtonSettings_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_changeCamera_clicked()
{
   bool was_playing = this->stream->isrunning;
   bool was_recording = this->capture->isRecording;

   // We cant change the video stream input of a recorded file,
   // so don't stop stream.
   if ( !stream->isReplay ) {
       stopAll();
   }

   if(videoStream == "/dev/video0") {
       videoStream = "/dev/video1";
       ui->cameraLabel->setText("Camera: Webcam");
   }
   else if(videoStream == "/dev/video1"){
        videoStream = "/dev/video0";
        ui->cameraLabel->setText("Camera: Built-In");
   }

   // We cant stop and then restart while recording
   if (was_playing && !was_recording) {
       QThread::usleep(.15);
      emit startCapture(videoStream);
      emit startStream();
      emit passNotifier(this->notifier.soundFiles);
   }
}

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

void MainWindow::on_QuitButton_clicked()
{
    emit clicked();
}

void MainWindow::on_Play_clicked()
{
    // TODO: Add logic for ReadData
    if(this->stream->isrunning)
    {
        stopAll();
        ui->Play->setText("Play");
    }
    else if (this->stream->isstopped)
    {
       emit startCapture(videoStream);
       emit startStream();
       ui->Play->setText("Stop");
    }
    else if (!this->stream->isrunning)
    {
        emit streamButtonClicked();
        emit startCapture(videoStream);
        emit startStream();
        ui->Play->setText("Stop");
    }
}

//Sets notification distance and sends value to objectdetectthead
void MainWindow::on_notificationDistanceSlider_valueChanged(int value)
{
    float newDistance = value/2.0;
    QString displayDist = QString::number(newDistance);
    ui->notifDistanceLabel->setText(displayDist + " m");
    emit setSigDist(newDistance);
}

void MainWindow::on_speechCheckBox_stateChanged()
{
    if(ui->beepCheckBox->isChecked()) {
        ui->beepCheckBox->setChecked(false);
    }
}

void MainWindow::on_beepCheckBox_stateChanged()
{
    if(ui->speechCheckBox->isChecked()) {
        ui->speechCheckBox->setChecked(false);
    }
}

void MainWindow::on_go_ReadFromFile_button_clicked()
{

    if (!this->stream->isrunning) {

//        ui->cameraLabel->setHidden(true);
//        ui->changeCamera->setEnabled(false);

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
            emit startCapture(videoFilename);

        }
        emit startRead(leddarFileName);
    }
}

void MainWindow::on_go_StreamFromDevice_button_clicked()
{
    // TODO: Add logic for ReadData
    // Check that LeddarStream is stopped
    if (!this->stream->isrunning && this->stream->isstopped) {
        updateSoundFiles();

        emit startCapture(videoStream);
        emit startStream();
    }
}

void MainWindow::on_go_Record_button_clicked()
{
    stopAll();
    // Check that stream is stopped
//    cout << this->stream->isrunning << endl;
//    cout << this->stream->isstopped << endl;
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

        emit emitStartVideoRecord(videoStream, videoFileName);
//        emit startStream();
        emit emitStartLeddarRecord(leddarFileName);

    } // if (!stream->isrunning && stream->isstopped) {
}

void MainWindow::on_go_StopAll_button_clicked()
{
    stopAll();
}
