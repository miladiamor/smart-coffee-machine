#pragma once
#include <QTimer>

class Koordinator;
#include <QMainWindow>
#include <QProgressBar>
#include <QImage>
#include <QTouchEvent>
#include <QPointF>
#include <QString>
class MainWindow;
#include "simulation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setSimulation(Simulation *sim);
    //void setKaffee(float kaffee);
signals:
    void sentTouch(QPointF lastTouch);

public slots:
    void updateWindow(const QImage &img);
    void updateWindowText(QString text);
    void updateKaffee(int kaffee);
private slots:
    /*void on_btnCappucino_clicked();

    void on_btnMilkCoffee_clicked();

    void on_btnCoffeeCrema_clicked();

    void on_btnLatteMachiato_clicked();
*/

    void on_pushButton_2_released();

    void on_pushButton_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Simulation *sim;
    Ui::MainWindow *ui;
    QProgressBar* cup;
};

