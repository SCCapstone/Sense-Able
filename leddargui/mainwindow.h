#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "leddarmain.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_readDataButton_clicked();

    void on_readDataButton_clicked(bool checked);

    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    QThread* leddarThread;
    LeddarStream* stream;

};

#endif // MAINWINDOW_H
