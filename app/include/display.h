#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QPointF>
#include <QImage>
#include <QString>

class Display : public QObject
{
    Q_OBJECT
public:
    explicit Display(QObject *parent = nullptr);
    ~Display();

    QPointF getLastTouch();
    void displayScreen(const QImage &img);
    void displayText(QString text);

signals:
    void updateDisplay(const QImage &img);
    void updateText(QString text);

public slots:
    void acceptTouch(QPointF &lastTouch);

private:
    QPointF lastTouch;
};

#endif // DISPLAY_H
