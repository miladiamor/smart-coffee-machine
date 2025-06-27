#pragma once

#include "Kaffeeprogramm.h"
#include "Zahlungseinheit.h"
#include "Programmsteuerung.h"

enum class KoordinatorZustand {
    WARTEN,
    ZUCKERWAHL,
    BEZAHLEN,
    AUSFUEHREN
};

class Koordinator {
private:
    Kaffeeprogramm kaffeeprogramm;
    Zahlungseinheit* zahlungseinheit;
    Programmsteuerung* programmsteuerung;
    KoordinatorZustand zustand;
    bool mitZucker;

public:
    Koordinator();

    // Getränkeauswahl
    void waehleCappuccino();
    void waehleMilchkaffee();
    void waehleKaffeeCrema();
    void waehleLatteMacchiato();

    // Zuckerwahl
    void waehleZucker(bool mitZucker);

    // Kauf und Ausführung
    void kaufeGetraenk();

    // Setup
    void setzeZahlungseinheit(Zahlungseinheit* z);
    void setzeProgrammsteuerung(Programmsteuerung* p);
};
