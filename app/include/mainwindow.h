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
signals:
    void sentTouch(QPointF lastTouch);

public slots:
    void updateWindow(const QImage &img);
    void updateWindowText(QString text);

private slots:
    /*void on_btnCappucino_clicked();

    void on_btnMilkCoffee_clicked();

    void on_btnCoffeeCrema_clicked();

    void on_btnLatteMachiato_clicked();
*/

    void on_pushButton_2_released();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Simulation *sim;
    Ui::MainWindow *ui;
    QProgressBar* cup;
};

