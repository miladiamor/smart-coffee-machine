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

signals:
    void sentTouch(QPointF &lastTouch);

public slots:
    void updateWindow(const QImage &img);
    void updateWindowText(QString text);

private slots:
    /*void on_btnCappucino_clicked();

    void on_btnMilkCoffee_clicked();

    void on_btnCoffeeCrema_clicked();

    void on_btnLatteMachiato_clicked();
*/

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::MainWindow *ui;
    QProgressBar* cup;
    Display *display;
};

