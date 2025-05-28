#include "Koordinator.h"

Koordinator::Koordinator()
    : fuellstandmessung(nullptr),
    anzeige(nullptr),
    zahlung(nullptr),
    steuerung(nullptr),
    mitZucker(false)
{
}

void Koordinator::setFuellstandsmessung(Fuellstandsmessung *fsm) {
    fuellstandmessung = fsm;
}

void Koordinator::setAnzeige(MainWindow *anzeigeWindow) {
    anzeige = anzeigeWindow;
}

void Koordinator::setZahlung(Zahlungseinheit *zahlungseinheit) {
    zahlung = zahlungseinheit;
}

void Koordinator::setSteuerung(Programmsteuerung *progSteuerung) {
    steuerung = progSteuerung;
}

bool Koordinator::bezahlen() {
    if (!zahlung) return false;

    Produkt* produkt = programm.getProdukt();
    if (!produkt) return false;

    return zahlung->versucheZahlung(produkt);
}

Kaffeeprogramm* Koordinator::getProgramm() {
    return &programm;
}
