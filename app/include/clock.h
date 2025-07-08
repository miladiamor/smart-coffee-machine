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

signals:
    void update();

public slots:
    void tick();

private:
    int ticks;
    QTimer timer;
};

#endif // CLOCK_H
