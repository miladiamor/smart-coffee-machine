#pragma once

#include "Kaffeeprogramm.h"
#include "Zahlungseinheit.h"
#include "Programmsteuerung.h"
#include "display.h"
#include <QPointF>
#include <QString>

// State enum
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
    Display* display;
    KoordinatorZustand zustand;
    bool mitZucker;

    QPointF lastTouch; // store last handled touch

    // Helper to show images from QRC
    void zeigeBild(const QString& pfad);

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

    void tick(); // renamed from update()
};
