#include "display.h"
#include <QString>
#include <QDebug>

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
    lastTouch = QPointF(0.0, 0.0);
    emit updateDisplay(img);
}

void Display::displayText(QString text) {
    qDebug() << "Aufgerufen2";
    emit updateText(text);
}

void Display::acceptTouch(QPointF lastTouch){
    this->lastTouch = lastTouch;
}


