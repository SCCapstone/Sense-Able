#include <qpushbutton.h>
#include "QtBehaviorTestSuite.h"
#include "mainwindow.h"

QtBehaviorTestSuite::QtBehaviorTestSuite() {
    cout << "\nStarting QtBehaviorTestSuite" << endl;
}

void QtBehaviorTestSuite::runTests() {

    this->testRecord();
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

    cout << "testMainPage: ";
    if(pagesSpy.count()==3) cout << "SUCCESS" << endl;
    else cout << "FAILURE" << endl;
}

/* Tests the stream from device button on the Stream page.
 * Returns SUCCESS if stream button clicked. Stops the stream
 * so other tests can be performed without interference.
 */
void QtBehaviorTestSuite::testStreamButtonClicked() {
    MainWindow window;

    // Set up a spy to check whether the Stream Button has been clicked.
    QSignalSpy clickedSpy(&window, SIGNAL(clickedButton()));
    QSignalSpy streamSpy(&window, SIGNAL(startStream()));    

    //Get the buttons
    QWidget *streamButton = window.findChild<QPushButton*>("streamButton");
    QWidget *fromDeviceButton = window.findChild<QPushButton*>("go_StreamFromDevice_button");
    QWidget *stopButton = window.findChild<QPushButton*>("go_StopAll_button");

    //Display incoming & outgoing signals
    //window.dumpObjectInfo();

    // Simulate clicking the buttons
    QTest::mouseClick(streamButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(fromDeviceButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(stopButton, Qt::LeftButton, Qt::NoModifier);

    cout << "\ntestStreamButtonClicked:  ";
    if (streamSpy.count() == 1){
        cout << "SUCCESS\n";
    }
    else cout << "FAILURE";

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
 * i.e. run their own functions if other threads are already running.
 * Returns SUCCESS if stream button clicked and read from file does *not* run.
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

    qDebug() << "Stream clicked: " << bool(streamSpy.count());
    qDebug() << "Read started: " << bool(readSpy.count());
    cout << "testButtonsClickable: ";
    if(streamSpy.count() && !readSpy.count()) {
        cout << "SUCCESS" << endl;
    }
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
    if(orientSpy.count()==1) {
        cout << "SUCCESS" << endl;
    }
    else cout << "FAILURE" << endl;
}

/* Tests recording function. When the button press is simulated, user can choose a file
 * name and the program will start recording. Outputs SUCCESS if both record button
 * and stop button clicked.
 */
void QtBehaviorTestSuite::testRecord() {
    MainWindow window;

    QSignalSpy recordSpy(&window, SIGNAL(StartVideoRecord(string,string)));
    QSignalSpy clickedSpy(&window,SIGNAL(clickedButton()));

    QWidget *recordButton = window.findChild<QPushButton*>("go_Record_button");
    QWidget *stopButton = window.findChild<QPushButton*>("go_StopAll_button");

    QTest::mouseClick(recordButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(stopButton, Qt::LeftButton, Qt::NoModifier);

    cout << "testRecord: ";
    if(clickedSpy.count() == 2) {
        cout << "SUCCESS" << endl;
    }
    else cout << "FAILURE" << endl;

    if(recordSpy.count() == 1) {
        cout << "testRecord: video record started succesfully";
    }
}
