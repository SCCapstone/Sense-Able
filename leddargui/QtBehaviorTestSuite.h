#ifndef QTBEHAVIORTESTSUITE_H
#define QTBEHAVIORTESTSUITE_H

#include <QObject>
#include <QWidget>
#include <QtTest/QtTest>
#include <QSignalSpy>

class QtBehaviorTestSuite : public QObject
{
    Q_OBJECT
public:
    explicit QtBehaviorTestSuite();

    void runTests();
    void testStreamButtonClicked();

signals:

public slots:

};

#endif // QTBEHAVIORTESTSUITE_H
