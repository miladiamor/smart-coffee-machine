#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Koordinator;
#include <QMainWindow>
#include <QProgressBar>
#include "Koordinator.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void cappucino();
    void milchkaffee();
    void kaffeeCrema();
    void latteMachiato();

    void zucker(bool mitZucker);
    void kaufen();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QProgressBar* cup;
    Koordinator *koordinator;
};

#endif // MAINWINDOW_H
