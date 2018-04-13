#ifndef QTBEHAVIORTESTSUITE_H
#define QTBEHAVIORTESTSUITE_H

#include <QObject>
#include <QWidget>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <mainwindow.h>
#include <QComboBox>

class QtBehaviorTestSuite : public QObject
{
    Q_OBJECT
public:
    explicit QtBehaviorTestSuite();

    //Runs all the tests in the test suite.
    void runTests();

    //Go page tests
    void testStreamButtonClicked();
    void testReadFunction();
    void testButtonClickable();
    void testOrientation();
    void testRecord();

    //Main page tests
    void testMainPage();

signals:

public slots:

};

#endif // QTBEHAVIORTESTSUITE_H
