/*********************************************************************
 * The usual main program for the Leddar streaming demo app.
 *
 * Date last modified: 8 December 2017
 * Author: Kathryn Vincent
***/

#include "mainwindow.h"
#include "gtest/gtest.h"
#include <QApplication>

/*********************************************************************
 * The usual main function for the Leddar streaming demo app.
***/
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
