#pragma once

#include "Kaffeeprogramm.h"
#include "Zahlungseinheit.h"
#include "Programmsteuerung.h"
#include "display.h" // Added to know Display type

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
    Display* display; // Declare display correctly

    KoordinatorZustand zustand;
    bool mitZucker;

public:
    Koordinator();

    void setzeDisplay(Display* d);
    void setzeProgrammsteuerung(Programmsteuerung* p);
    void setzeZahlungseinheit(Zahlungseinheit* z);

    void waehleCappuccino();
    void waehleMilchkaffee();
    void waehleKaffeeCrema();
    void waehleLatteMacchiato();
    void waehleZucker(bool mitZucker);
    void fuehreKaufDurch();
    void verarbeiteTouch(const QPointF& position);
};
