#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QTimer>
#include <QTime>

class Clock : public QObject
{
    Q_OBJECT

public:
    Clock(int framerate = 20);
    void start();
    void stop();

signals:
    void update();

public slots:
    void tick();

private:
    QTimer timer;
    QTime lastStartTime;
};

#endif // CLOCK_H
