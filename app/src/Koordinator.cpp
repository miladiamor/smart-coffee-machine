#include "Koordinator.h"

Koordinator::Koordinator()
    : zahlung(nullptr),
    steuerung(nullptr),
    state(KoordinatorStates::WARTEN),
    mitZucker(false),
    milchFrageNotwendig(false),
    mitMilch(false)
{}

void Koordinator::setZahlungseinheit(Zahlungseinheit* z) {
    zahlung = z;
}

void Koordinator::setSteuerung(Programmsteuerung* steuerung) {
    this->steuerung = steuerung;
}

void Koordinator::cappuccino() {
    programm.setKaffeemenge_g(9);
    programm.setWassermenge_ml(30);
    programm.setWasserKochhitze_Cel(93);
    programm.setMilchZuerst(true);

    milchFrageNotwendig = true;
    state = KoordinatorStates::MILCH;
}

void Koordinator::milchkaffee() {
    programm.setKaffeemenge_g(9);
    programm.setWassermenge_ml(30);
    programm.setWasserKochhitze_Cel(92);
    programm.setMilchZuerst(true);

    milchFrageNotwendig = true;
    state = KoordinatorStates::MILCH;
}

void Koordinator::kaffeeCrema() {
    programm.setKaffeemenge_g(9);
    programm.setWassermenge_ml(80);
    programm.setWasserKochhitze_Cel(95);
    programm.setMilchZuerst(false);

    programm.setMilchmenge_ml(0);
    programm.setMilchKochhitze_Cel(0);
    milchFrageNotwendig = false;

    state = KoordinatorStates::ZUCKER;
}

void Koordinator::latteMacchiato() {
    programm.setKaffeemenge_g(9);
    programm.setWassermenge_ml(30);
    programm.setWasserKochhitze_Cel(92);
    programm.setMilchZuerst(true);

    milchFrageNotwendig = true;
    state = KoordinatorStates::MILCH;
}

void Koordinator::milchWaehlen(bool mitMilch) {
    this->mitMilch = mitMilch;

    if (mitMilch) {
        // Default milk config or adjust by drink type if needed
        programm.setMilchmenge_ml(120);
        programm.setMilchKochhitze_Cel(65);
    } else {
        programm.setMilchmenge_ml(0);
        programm.setMilchKochhitze_Cel(0);
    }

    state = KoordinatorStates::ZUCKER;
}

void Koordinator::zuckerWaehlen(bool mitZucker) {
    this->mitZucker = mitZucker;
    programm.setMitZucker(mitZucker);
    state = KoordinatorStates::BEZAHLEN;
}

void Koordinator::kaufen() {
    if (!zahlung) return;

    Produkt* produkt = programm.getProdukt();
    if (!produkt) return;

    bool bezahlt = zahlung->versucheZahlung(produkt);
    if (bezahlt) {
        state = KoordinatorStates::AUSFUEHREN;
        if (steuerung) {
            steuerung->ausfuehren(&programm);
        }
    } else {
        state = KoordinatorStates::WARTEN;
    }
}
