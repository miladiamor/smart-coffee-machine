#include "display.h"
#include <QDebug>
#include "mainwindow.h"

Display::Display(QObject *parent)
    : QObject{parent}, mw(nullptr)
{
}

Display::~Display()
{
}

QPointF Display::getLastTouch() {
    return lastTouch;
}

void Display::acceptTouch(QPointF &lastTouch) {
    this->lastTouch = lastTouch;
    qDebug() << "Touch accepted at:" << lastTouch;
}

void Display::setMainWindow(MainWindow *mw) {
    this->mw = mw;
}

void Display::displayScreen(const QImage &img) {
    if (mw) {
        mw->displayScreen(img);
    }
}

