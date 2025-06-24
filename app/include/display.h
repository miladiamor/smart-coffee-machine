#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QPointF>
#include <QImage>
#include <QPainter>
class MainWindow;

class Display : public QObject
{
    Q_OBJECT
public:
    explicit Display(QObject *parent = nullptr);
    ~Display();

    QPointF getLastTouch();
    void displayScreen(const QImage &img);

    void setMainWindow(MainWindow *mw);

    void displaySelection();

public slots:
    void acceptTouch(QPointF &lastTouch);

private:
    QPointF lastTouch;
    MainWindow *mw;
};

#endif // DISPLAY_H
