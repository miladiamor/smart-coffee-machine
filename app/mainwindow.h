#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>

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
};

#endif // MAINWINDOW_H
