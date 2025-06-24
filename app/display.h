#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QPointF>
class Display;
#include "mainwindow.h"

class Display : public QObject
{
    Q_OBJECT
public:
    explicit Display(QObject *parent = nullptr);
    ~Display();

    QPointF getTouch();
    void displayScreen(const QImage &img);

    void setMainWindow(MainWindow *mw);

public slots:
    void acceptTouch(QPointF &lastTouch);

private:
    QPointF lastTouch;
    MainWindow *mw;
};

#endif // DISPLAY_H
