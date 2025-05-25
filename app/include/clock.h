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
    void update(int delta_t_ms);

public slots:
    void tick();

private:
    int framerate;
    QTimer timer;
    QTime lastStartTime;
};

#endif // CLOCK_H
