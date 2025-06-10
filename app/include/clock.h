#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QTimer>
#include <QTime>

class Clock : public QObject
{
    Q_OBJECT

public:
    Clock(int ticks);
    void start();
    void stop();

signals:
    void update();

public slots:
    void tick();

private:
    int ticks;
    QTimer timer;
    QTime lastStartTime;
};

#endif // CLOCK_H
