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

void Display::displaySelection() {
    // Create an image with white background
    QImage img(400, 400, QImage::Format_ARGB32);
    img.fill(Qt::white);

    QPainter painter(&img);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));

    // Draw option labels
    painter.drawText(50, 100, "Cappuccino");
    painter.drawText(250, 100, "Milchkaffee");
    painter.drawText(50, 250, "KaffeeCrema");
    painter.drawText(250, 250, "LatteMacchiato");

    // Optionally draw circles or bounding boxes for buttons
    painter.setBrush(Qt::lightGray);
    painter.drawEllipse(QPointF(50, 100), 40, 20);
    painter.drawEllipse(QPointF(250, 100), 40, 20);
    painter.drawEllipse(QPointF(50, 250), 40, 20);
    painter.drawEllipse(QPointF(250, 250), 40, 20);

    painter.end();

    // Send image to UI
    displayScreen(img);
}
