#include <qpushbutton.h>
#include "QtBehaviorTestSuite.h"
#include "mainwindow.h"

QtBehaviorTestSuite::QtBehaviorTestSuite() {
    cout << "\nStarting QtBehaviorTestSuite" << endl;
}

void QtBehaviorTestSuite::runTests() {
    this->testStreamButtonClicked();
}

void QtBehaviorTestSuite::testStreamButtonClicked() {
    MainWindow window;

    // Set up a spy to check whether the Stream Button has been clicked.
    QSignalSpy spy(&window, SIGNAL(streamButtonClicked()));


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

    cout << "testStreamButtonClicked:  ";
    if (spy.count() == 1) {
        cout << "SUCCESS";
    } else {
        cout << "FAILURE";
    }
    cout << endl;
    cout << "Spy count: " << spy.count() << endl;

    // Can't get this to output to the console:
    //QCOMPARE(spy.count(), 1);
}
