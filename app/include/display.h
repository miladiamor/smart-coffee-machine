#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QPointF>
#include <QImage>

class Display : public QObject
{
    Q_OBJECT
public:
    explicit Display(QObject *parent = nullptr);
    ~Display();

    QPointF getLastTouch();
    void displayScreen(const QImage &img);

signals:
    void updateDisplay(const QImage &img);

public slots:
    void acceptTouch(QPointF &lastTouch);

private:
    QPointF lastTouch;
};

#endif // DISPLAY_H
