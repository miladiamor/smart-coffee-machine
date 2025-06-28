#pragma once

#include <QMainWindow>
#include <QProgressBar>
#include <QImage>
#include <QTouchEvent>
#include <QPointF>
#include <QTimer>

#include "display.h"
#include "Koordinator.h"

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
    void updateSystem();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::MainWindow *ui;
    QProgressBar* cup;
    Display *display;
    Koordinator *koordinator;
    Programmsteuerung *programmsteuerung;
    QTimer *updateTimer;
};
