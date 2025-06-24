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
    mw->displayScreen(img);
}

void Display::acceptTouch(QPointF &lastTouch){
    this->lastTouch = lastTouch;
}

void Display::setMainWindow(MainWindow *mw){
    this->mw = mw;
}
