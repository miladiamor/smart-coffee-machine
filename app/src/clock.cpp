#include "clock.h"

Clock::Clock(int ticks) : QObject(nullptr), ticks(ticks) {
    QObject::connect(&timer, &QTimer::timeout, this, &Clock::tick);
}

void Clock::start(){
    timer.start();
}

void Clock::stop(){
    timer.stop();
}

void Clock::tick(){
    emit update();
}
