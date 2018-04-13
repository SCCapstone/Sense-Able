#include <qpushbutton.h>
#include "QtBehaviorTestSuite.h"
#include "mainwindow.h"

QtBehaviorTestSuite::QtBehaviorTestSuite() {
    cout << "\nStarting QtBehaviorTestSuite" << endl;
}

void QtBehaviorTestSuite::runTests() {

    //this->testRecord();
    this->testMainPage();
    this->testStreamButtonClicked();
    this->testReadFunction();
    this->testButtonClickable();
    this->testOrientation();
}

/* Tests all buttons on the Home page. Returns SUCCESS if signal spy
 * catches the clickedButton signal for all 3 buttons.
 */
void QtBehaviorTestSuite::testMainPage(){
    MainWindow window;

    QSignalSpy pagesSpy(&window, SIGNAL(clickedButton()));

    QWidget *streamButton = window.findChild<QPushButton*>("streamButton");
    QWidget *settingsButton = window.findChild<QPushButton*>("settingsPageButton");
    QWidget *quitButton = window.findChild<QPushButton*>("QuitButton");

    QTest::mouseClick(streamButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(settingsButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(quitButton, Qt::LeftButton, Qt::NoModifier);
    //pagesSpy.wait(1000);
    qDebug() << "Main page click count: " << pagesSpy.count();
    cout << "testMainPage: ";
    if(pagesSpy.count()==3) cout << "SUCCESS" << endl;
    else cout << "FAILURE" << endl;
}

// TODO: Make all outputs the same format, QCOMPARE(spy.count(), 1) would be great if it worked
void QtBehaviorTestSuite::testStreamButtonClicked() {
    MainWindow window;
   // QThread capture = MainWindow.captureThread;

    // Set up a spy to check whether the Stream Button has been clicked.
    //QSignalSpy spy(&window, SIGNAL(streamButtonClicked()));
    QSignalSpy clickedSpy(&window, SIGNAL(clickedButton()));
    QSignalSpy streamSpy(&window, SIGNAL(startStream()));
    //QSignalSpy captureSpy(&window, SIGNAL(capture.isRunning());

    //Get the buttons
    QWidget *streamButton = window.findChild<QPushButton*>("streamButton");
    QWidget *fromDeviceButton = window.findChild<QPushButton*>("go_StreamFromDevice_button");
    QWidget *stopButton = window.findChild<QPushButton*>("go_StopAll_button");
    //QWidget *backButton = window.findChild<QPushButton*>("backButtonGo");

    //Display incoming & outgoing signals
    //window.dumpObjectInfo();

    // Simulate clicking the buttons
    QTest::mouseClick(streamButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(fromDeviceButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(stopButton, Qt::LeftButton, Qt::NoModifier);
    //QTest::mouseClick(backButton, Qt::LeftButton, Qt::NoModifier);

    /*cout << "\ntestStreamButtonClicked:  ";
    if (spy.count() == 1) {
        cout << "SUCCESS\n";
    } else {
        cout << "FAILURE\n";
    }*/
    cout << "testStartStream: ";
    if (streamSpy.count() == 1){
        cout << "SUCCESS\n";
    }
    else cout << "FAILUER\n";
    cout << "\nSpy count: " << clickedSpy.count() << endl;

    cout << "capture thread running: ";
   // if(captureSpy()==1) cout << "SUCCESS";
    //else cout << "FAILURE";

    // Can't get this to output to the console:
    //QCOMPARE(spy.count(), 1);
}

/* Tests the Read From File function on the Stream page.
 * Returns SUCCESS if start read function is initiated, even if
 * no file name is provided.
 */
void QtBehaviorTestSuite::testReadFunction(){
    MainWindow window;
    QSignalSpy readSpy(&window, SIGNAL(startRead(string)));

    QWidget *readButton = window.findChild<QPushButton*>("go_ReadFromFile_button");
    QWidget *stopButton = window.findChild<QPushButton*>("go_StopAll_button");

    QTest::mouseClick(readButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(stopButton, Qt::LeftButton, Qt::NoModifier);

    cout << "\ntestReadFunction:  ";
    if (readSpy.count() == 1) {
        cout << "SUCCESS\n";
    } else {
        cout << "FAILURE\n";
    }
}

/* Tests whether buttons are "clickable" after other buttons pressed,
 * i.e. run their own functions if other threads are already running
 * (They shouldn't do that)
 */
void QtBehaviorTestSuite::testButtonClickable(){
    MainWindow window;

    QSignalSpy streamSpy(&window, SIGNAL(streamButtonClicked()));
    QSignalSpy readSpy(&window, SIGNAL(startRead(string)));

    QWidget *fromDeviceButton = window.findChild<QPushButton*>("go_StreamFromDevice_button");
    QWidget *readButton = window.findChild<QPushButton*>("go_ReadFromFile_button");
    QWidget *stopButton = window.findChild<QPushButton*>("go_StopAll_button");


    QTest::mouseClick(fromDeviceButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(readButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(stopButton, Qt::LeftButton, Qt::NoModifier);


    //QCOMPARE(streamSpy.count(),1);
    //QCOMPARE(readSpy.count(),0);
    //readSpy.wait(1000);
    qDebug() << "Stream clicked: " << bool(streamSpy.count());
    qDebug() << "Read started: " << bool(readSpy.count());
    cout << "testButtonsClickable: ";
    if(streamSpy.count() && !readSpy.count()) cout << "SUCCESS" << endl;
    else cout << "FAILURE" << endl;
}

/* Tests the Change Orientation button on the Stream page. If the setLeddarOrientation
 * signal is sent, this is outputs SUCCESS.
 */
void QtBehaviorTestSuite::testOrientation() {
    MainWindow window;

    QSignalSpy orientSpy(&window, SIGNAL(setLeddarOrientation(bool)));

    QWidget *orientButton = window.findChild<QPushButton*>("changeOrient");

    QTest::mouseClick(orientButton, Qt::LeftButton, Qt::NoModifier);

    cout << "testOrientation: ";
    if(orientSpy.count()==1) cout << "SUCCESS" << endl;
    else cout << "FAILURE" << endl;
}

/* Tests recording function. When the button press is simulated, user can choose a file
 * name and the program will start recording. If no file name is selected this will
 * return FAILURE. TODO: pass file name so no interaction required? how
 */
void QtBehaviorTestSuite::testRecord() {
    MainWindow window;

    QSignalSpy recordSpy(&window, SIGNAL(StartVideoRecord(string,string)));
    //QSignalSpy timeSpy(&window,SIGNAL(clickedButton()));

    QWidget *recordButton = window.findChild<QPushButton*>("go_Record_button");
    QWidget *stopButton = window.findChild<QPushButton*>("go_StopAll_button");

    QTest::mouseClick(recordButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(stopButton, Qt::LeftButton, Qt::NoModifier);

    cout << "testRecord: ";
    if(recordSpy.count()==1) cout << "SUCCESS" << endl;
    else cout << "FAILURE" << endl;
}
