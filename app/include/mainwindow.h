#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Koordinator;
#include <QMainWindow>
#include <QProgressBar>
#include "display.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnCappucino_clicked();

    void on_btnMilkCoffee_clicked();

private:
    Ui::MainWindow *ui;
    QProgressBar* cup;
    Display display;
};

#endif // MAINWINDOW_H
