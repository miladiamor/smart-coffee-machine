#include "display.h"

Display::Display(QObject *parent)
    : QObject{parent}
{
}

Display::~Display(){

}

QPointF Display::getLastTouch() {
    return this->lastTouch;
}
void Display::displayScreen(const QImage &img) {
    emit updateDisplay(img);
}

void Display::acceptTouch(QPointF &lastTouch){
    this->lastTouch = lastTouch;
}


