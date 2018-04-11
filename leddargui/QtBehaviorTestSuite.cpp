#include <qpushbutton.h>
#include "QtBehaviorTestSuite.h"
#include "mainwindow.h"

QtBehaviorTestSuite::QtBehaviorTestSuite() {
    cout << "\nStarting QtBehaviorTestSuite" << endl;
}

void QtBehaviorTestSuite::runTests() {
    this->testStreamButtonClicked();
    this->testReadFunction();
}

void QtBehaviorTestSuite::testStreamButtonClicked() {
    MainWindow window;

    // Set up a spy to check whether the Stream Button has been clicked.
    QSignalSpy spy(&window, SIGNAL(streamButtonClicked()));
    QSignalSpy clickedSpy(&window, SIGNAL(clicked()));
    QSignalSpy streamSpy(&window, SIGNAL(startStream()));



    //Get the buttons
    QWidget *streamButton = window.findChild<QPushButton*>("streamButton");
    QWidget *fromDeviceButton = window.findChild<QPushButton*>("go_StreamFromDevice_button");
    QWidget *stopButton = window.findChild<QPushButton*>("go_StopAll_button");
    QWidget *quitButton = window.findChild<QPushButton*>("QuitButton");
    QWidget *backButton = window.findChild<QPushButton*>("backButtonGo");

    //Display incoming & outgoing signals
    //window.dumpObjectInfo();
    //streamButton->dumpObjectInfo();
    //quitButton->dumpObjectInfo();

    // Simulate clicking the buttons
    QTest::mouseClick(streamButton, Qt::LeftButton);
    QTest::mouseClick(fromDeviceButton, Qt::LeftButton);
    QTest::mouseClick(stopButton, Qt::LeftButton, Qt::NoModifier);
    //QTest::mouseClick(readButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(quitButton, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(backButton, Qt::LeftButton, Qt::NoModifier);

    cout << "\ntestStreamButtonClicked:  ";
    if (spy.count() == 1) {
        cout << "SUCCESS";
    } else {
        cout << "FAILURE";
    }
    cout << "\nstartStream test: ";
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
    QSignalSpy wat(&window, SIGNAL(startCapture(string)));

    QWidget *readButton = window.findChild<QPushButton*>("go_ReadFromFile_button");

    QTest::mouseClick(readButton, Qt::LeftButton, Qt::NoModifier);

    cout << "\ntest startRead sent:  ";
    if (readSpy.count() == 1) {
        cout << "SUCCESS";
    } else {
        cout << "FAILURE";
    }
}
