#pragma once

#include "Kaffeeprogramm.h"
#include "Zahlungseinheit.h"
#include "Programmsteuerung.h"

enum class KoordinatorStates {
    WARTEN,
    MILCH,
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
    bool milchFrageNotwendig;
    bool mitMilch;

public:
    Koordinator();

    // Drink selection
    void cappuccino();
    void milchkaffee();
    void kaffeeCrema();
    void latteMacchiato();

    // User preferences
    void milchWaehlen(bool mitMilch);
    void zuckerWaehlen(bool mitZucker);
    void kaufen();

    void setZahlungseinheit(Zahlungseinheit* z);
    void setSteuerung(Programmsteuerung* steuerung);
};
