/*********************************************************************
 * The usual main program for the Leddar streaming demo app.
 *
 * Date last modified: 8 December 2017
 * Author: Kathryn Vincent
***/

#include "mainwindow.h"
#include "gtest/gtest.h"
#include "QtBehaviorTestSuite.h"
#include <QApplication>

/*********************************************************************
 * The usual main function for the Leddar streaming demo app.
***/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Perform unit tests.
    ::testing::InitGoogleTest(&argc, argv);
<<<<<<< HEAD
//    RUN_ALL_TESTS();

    // Perform behavioral tests.
    QtBehaviorTestSuite suite;
//    suite.runTests();
=======
    RUN_ALL_TESTS();

    // Perform behavioral tests.
//    QtBehaviorTestSuite suite;
    //suite.runTests();
>>>>>>> 4d8efbab7efcf8f5af78dbd3a3be928990a15f30

    // Show the app.
    w.show();
    return a.exec();
}
