#include "clock.h"

Clock::Clock(int ticks) : QObject(nullptr), ticks(ticks) {
    QObject::connect(&timer, &QTimer::timeout, this, &Clock::tick);
    timer.start(1000 / ticks);
}

void Clock::tick(){
    emit update();
}
