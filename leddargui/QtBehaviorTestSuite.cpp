#include <qpushbutton.h>
#include "QtBehaviorTestSuite.h"
#include "mainwindow.h"

QtBehaviorTestSuite::QtBehaviorTestSuite() {
    cout << "\nStarting QtBehaviorTestSuite" << endl;
}

void QtBehaviorTestSuite::runTests() {

    this->testStreamButtonClicked();
    this->testReadFunction();
    this->testButtonClickable();
    this->testMainPage();
}

// TODO: Make all outputs the same format, QCOMPARE(spy.count(), 1) would be great if it worked
void QtBehaviorTestSuite::testStreamButtonClicked() {
    MainWindow window;

    // Set up a spy to check whether the Stream Button has been clicked.
    QSignalSpy spy(&window, SIGNAL(streamButtonClicked()));
    QSignalSpy clickedSpy(&window, SIGNAL(clickedButton()));
    QSignalSpy streamSpy(&window, SIGNAL(startStream()));

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

    cout << "\ntestStreamButtonClicked:  ";
    if (spy.count() == 1) {
        cout << "SUCCESS\n";
    } else {
        cout << "FAILURE\n";
    }
    cout << "testStartStream: ";
    if (streamSpy.count() == 1){
        cout << "SUCCESS\n";
    }
    else cout << "FAILUER\n";
    cout << endl;
    cout << "Spy count: " << clickedSpy.count() << endl;


    // Can't get this to output to the console:
    //QCOMPARE(spy.count(), 1);
}

void QtBehaviorTestSuite::testReadFunction(){
    MainWindow window;
    QSignalSpy readSpy(&window, SIGNAL(startRead(string)));
    QSignalSpy captureSpy(&window, SIGNAL(startCapture(string)));

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
