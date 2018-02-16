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
    QWidget *button = window.findChild<QPushButton*>("streamButton");
    //QWidget *readButton = window.findChild<QPushButton*>("readDataButton");

    // Simulate clicking the buttons
    QWidget *cancelButton = window.findChild<QPushButton*>("cancelButton");
    QTest::mouseClick(button, Qt::LeftButton, Qt::NoModifier);
    QTest::mouseClick(cancelButton, Qt::LeftButton, Qt::NoModifier);
    //QTest::mouseClick(readButton, Qt::LeftButton, Qt::NoModifier);


    cout << "testStreamButtonClicked:  ";
    if (spy.count() == 1) {
        cout << "SUCCESS";
    } else {
        cout << "FAILURE";
    }
    cout << endl;

    // Can't get this to output to the console:
    // QCOMPARE(spy.count(), 1);
}
