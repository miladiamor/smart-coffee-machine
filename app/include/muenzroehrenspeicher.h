#ifndef MUENZROEHRENSPEICHER_H
#define MUENZROEHRENSPEICHER_H

#include "Muenzroehre.h"
#include "Muenzenschieber.h"
#include "MuenzAuswerfer.h"

class Muenzroehrenspeicher {
private:
    Muenzroehre* roehre2Euro;
    Muenzroehre* roehre1Euro;
    Muenzroehre* roehre50Cent;
    Muenzroehre* roehre20Cent;
    Muenzroehre* roehre10Cent;

    Muenzenschieber* schieber;
    MuenzAuswerfer* auswerfer;

public:
    // Standardkonstruktor fuer Unittests
    Muenzroehrenspeicher();

    // Konstruktor mit Abhaengigkeiten
    Muenzroehrenspeicher(Muenzroehre* r2, Muenzroehre* r1, Muenzroehre* r50,
                         Muenzroehre* r20, Muenzroehre* r10,
                         Muenzenschieber* schieber, MuenzAuswerfer* auswerfer);

    bool fuegeMuenzeEin(float wert);
    void muenzeAuswerfen(float wert);
    void geldAuswerfen(float betrag); // wirft mehrere Münzen aus
};

#endif
