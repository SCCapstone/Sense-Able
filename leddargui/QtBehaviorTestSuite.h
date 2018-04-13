#ifndef QTBEHAVIORTESTSUITE_H
#define QTBEHAVIORTESTSUITE_H

#include <QObject>
#include <QWidget>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <mainwindow.h>

class QtBehaviorTestSuite : public QObject
{
    Q_OBJECT
public:
    explicit QtBehaviorTestSuite();

    void runTests();
    void testStreamButtonClicked();
    void testReadFunction();
    void testButtonClickable();
    void testMainPage();

signals:

public slots:

};

#endif // QTBEHAVIORTESTSUITE_H
