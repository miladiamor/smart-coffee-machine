#include "display.h"

Display::Display(QObject *parent)
    : QObject{parent}
{
}

Display::~Display(){

}

bool Display::getNewTouchEvent(){
    bool ret = newTouchEvent;
    newTouchEvent = false;
    return ret;
}

Position Display::getTouchEvent(){
    return touchEvent;
}

void Display::update(int x, int y) {
    touchEvent.x = x;
    touchEvent.y = y;
    newTouchEvent = true;
}
