#pragma once

#include <QPointF>
#include <QString>
#include <QImage>

#include "Kaffeeprogramm.h"
#include "Programmsteuerung.h"
#include "Zahlungseinheit.h"
#include "Fuellstandsmessung.h"
#include "Display.h"

enum class KoordinatorZustand {
    WARTEN,
    ZUCKERWAHL,
    BEZAHLEN,
    AUSFUEHREN,
    WARTEN_AUF_FERTIG,
    FERTIG
};

class Koordinator {
private:
    Kaffeeprogramm* kaffeeprogramm = nullptr;
    Programmsteuerung* programmsteuerung = nullptr;
    Zahlungseinheit* zahlungseinheit = nullptr;
    Fuellstandsmessung* fuellstandsmessung = nullptr;
    Display* display = nullptr;

    KoordinatorZustand zustand = KoordinatorZustand::WARTEN;
    bool mitZucker = false;
    QPointF lastTouch;

    void zeigeBild(const QString& pfad);

public:
    Koordinator();

    void setzeDisplay(Display* d);
    void setzeProgrammsteuerung(Programmsteuerung* p);
    void setzeZahlungseinheit(Zahlungseinheit* z);
    void setzeFuellstandsmessung(Fuellstandsmessung* f);

    void tick();

    KoordinatorZustand getZustand() const {
        return zustand;
    }
};
