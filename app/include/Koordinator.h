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

    // Helper to show images from QRC
    void zeigeBild(const QString& pfad);

public:
    // Constructor
    Koordinator();

    // Setters for dependency injection
    void setzeDisplay(Display* d);
    void setzeProgrammsteuerung(Programmsteuerung* p);
    void setzeZahlungseinheit(Zahlungseinheit* z);

    // Getränkeauswahl
    void waehleCappuccino();
    void waehleMilchkaffee();
    void waehleKaffeeCrema();
    void waehleLatteMacchiato();

    // Zuckerwahl
    void waehleZucker(bool mitZucker);

    // Kauf und Ausführung
    void fuehreKaufDurch();

    // Touch-Verarbeitung
    void verarbeiteTouch(const QPointF& position);

    // To handle post-brewing cleanup
    void update();
};
