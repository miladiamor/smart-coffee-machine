#include "Koordinator.h"
#include <QPainter>
#include <QImage>

Koordinator::Koordinator()
    : zahlung(nullptr),
    steuerung(nullptr),
    display(nullptr),
    state(KoordinatorStates::WARTEN),
    mitZucker(false)
{}

void Koordinator::setZahlungseinheit(Zahlungseinheit* z) {
    zahlung = z;
}

void Koordinator::setSteuerung(Programmsteuerung* steuerung) {
    this->steuerung = steuerung;
}

void Koordinator::setDisplay(Display* d) {
    this->display = d;
}

void Koordinator::zeigeAuswahl() {
    QImage img(400, 400, QImage::Format_ARGB32);
    img.fill(Qt::white);

    QPainter painter(&img);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));

    // Draw drink names
    painter.drawText(50, 100, "Cappuccino");
    painter.drawText(250, 100, "Milchkaffee");
    painter.drawText(50, 250, "KaffeeCrema");
    painter.drawText(250, 250, "LatteMacchiato");

    // Draw selection hitboxes
    painter.setBrush(Qt::lightGray);
    painter.drawEllipse(QPointF(50, 100), 40, 20);
    painter.drawEllipse(QPointF(250, 100), 40, 20);
    painter.drawEllipse(QPointF(50, 250), 40, 20);
    painter.drawEllipse(QPointF(250, 250), 40, 20);

    painter.end();

    if (display) {
        display->displayScreen(img);
    }
}

// DRINK SELECTION
void Koordinator::cappuccino() {
    programm.setKaffeemenge_g(9);
    programm.setWassermenge_ml(30);
    programm.setMilchmenge_ml(120);
    programm.setWasserKochhitze_Cel(93);
    programm.setMilchKochhitze_Cel(65);
    programm.setMilchZuerst(true);
    state = KoordinatorStates::ZUCKER;
}

void Koordinator::milchkaffee() {
    programm.setKaffeemenge_g(9);
    programm.setWassermenge_ml(30);
    programm.setMilchmenge_ml(150);
    programm.setWasserKochhitze_Cel(92);
    programm.setMilchKochhitze_Cel(70);
    programm.setMilchZuerst(true);
    state = KoordinatorStates::ZUCKER;
}

void Koordinator::kaffeeCrema() {
    programm.setKaffeemenge_g(9);
    programm.setWassermenge_ml(80);
    programm.setMilchmenge_ml(0);
    programm.setWasserKochhitze_Cel(95);
    programm.setMilchKochhitze_Cel(0);
    programm.setMilchZuerst(false);
    state = KoordinatorStates::ZUCKER;
}

void Koordinator::latteMacchiato() {
    programm.setKaffeemenge_g(9);
    programm.setWassermenge_ml(30);
    programm.setMilchmenge_ml(200);
    programm.setWasserKochhitze_Cel(92);
    programm.setMilchKochhitze_Cel(60);
    programm.setMilchZuerst(true);
    state = KoordinatorStates::ZUCKER;
}

// USER CHOICES
void Koordinator::zuckerWaehlen(bool mitZucker) {
    this->mitZucker = mitZucker;
    programm.setMitZucker(mitZucker);
    state = KoordinatorStates::BEZAHLEN;
}

// PAYMENT + EXECUTION
void Koordinator::kaufen() {
    if (!zahlung) return;

    Produkt* produkt = programm.getProdukt();
    if (!produkt) return;

    bool bezahlt = false;
    //bezahlt = zahlung->versucheZahlung(produkt);
    if (bezahlt) {
        state = KoordinatorStates::AUSFUEHREN;
        if (steuerung) {
            steuerung->ausfuehren(&programm);
        }
    } else {
        state = KoordinatorStates::WARTEN;
    }
}
