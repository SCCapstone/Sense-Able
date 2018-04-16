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

    //srand (time(NULL)); //initialize random seed to simulate noise in unit test (stdlib.h)
    // Perform unit tests.
//    ::testing::InitGoogleTest(&argc, argv);
    //RUN_ALL_TESTS();

    // Perform behavioral tests.
    //QtBehaviorTestSuite suite;
    //suite.runTests();

    // Show the app.
    w.show();
    return a.exec();
}
