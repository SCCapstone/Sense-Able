#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

class Worker : public QObject {
    Q_OBJECT

public slots:
    void runLeddarMain();
};

#endif // MAINWINDOW_H
