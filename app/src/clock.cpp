#include "clock.h"

Clock::Clock(int framerate) : QObject(nullptr), framerate(framerate) {
    timer.setInterval(1000 / framerate);
    QObject::connect(&timer, &QTimer::timeout, this, &Clock::tick);
}

void Clock::start(){
    timer.start();
}

void Clock::stop(){
    timer.stop();
}

void Clock::tick(){
    int delta_t_ms = 1000 / framerate;
    emit update(delta_t_ms);
}
