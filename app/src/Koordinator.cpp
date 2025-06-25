#include "Koordinator.h"

Koordinator::Koordinator()
    : zahlung(nullptr),
    steuerung(nullptr),
    state(KoordinatorStates::WARTEN),
    mitZucker(false)
{}

void Koordinator::setZahlungseinheit(Zahlungseinheit* z) {
    zahlung = z;
}

void Koordinator::setSteuerung(Programmsteuerung* steuerung) {
    this->steuerung = steuerung;
}

// DRINK RECIPES
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

// SUGAR SELECTION
void Koordinator::zuckerWaehlen(bool mitZucker) {
    this->mitZucker = mitZucker;
    programm.setMitZucker(mitZucker);
    state = KoordinatorStates::BEZAHLEN;
}

// PAYMENT + START PROGRAM
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
