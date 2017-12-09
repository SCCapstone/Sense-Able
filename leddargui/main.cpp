/*********************************************************************
 * The usual main program for the Leddar streaming demo app.
 *
 * Date last modified: 8 December 2017
 * Author: Kathryn Vincent
***/

#include "mainwindow.h"
#include <QApplication>

/*********************************************************************
 * The usual main function for the Leddar streaming demo app.
***/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
