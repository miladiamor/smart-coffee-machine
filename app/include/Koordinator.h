#pragma once

#include "Kaffeeprogramm.h"
#include "Zahlungseinheit.h"
#include "Programmsteuerung.h"

enum class KoordinatorStates {
    WARTEN,
    ZUCKER,
    BEZAHLEN,
    AUSFUEHREN
};

class Koordinator {
private:
    Kaffeeprogramm programm;
    Zahlungseinheit* zahlung;
    Programmsteuerung* steuerung;
    KoordinatorStates state;
    bool mitZucker;

public:
    Koordinator();

    // Drink selection
    void cappuccino();
    void milchkaffee();
    void kaffeeCrema();
    void latteMacchiato();

    // User choices
    void zuckerWaehlen(bool mitZucker);
    void kaufen();

    // Setup
    void setZahlungseinheit(Zahlungseinheit* z);
    void setSteuerung(Programmsteuerung* steuerung);
};
