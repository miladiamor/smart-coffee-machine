#ifndef MUENZROEHRENSPEICHER_H
#define MUENZROEHRENSPEICHER_H

#include "Muenzroehre.h"
#include "Muenzenschieber.h"
#include "MuenzAuswerfer.h"
#include <map>

class Muenzroehrenspeicher {
private:
    std::map<int, float> muenzen;

    Muenzroehre* roehre2Euro;
    Muenzroehre* roehre1Euro;
    Muenzroehre* roehre50Cent;
    Muenzroehre* roehre20Cent;
    Muenzroehre* roehre10Cent;

    Muenzenschieber* schieber;
    MuenzAuswerfer* auswerfer;

public:
    Muenzroehrenspeicher(Muenzroehre* r2, Muenzroehre* r1, Muenzroehre* r50,
                         Muenzroehre* r20, Muenzroehre* r10,
                         Muenzenschieber* schieber, MuenzAuswerfer* auswerfer);
    Muenzroehrenspeicher(); // Dummy Konstruktor fuer Tests


    bool fuegeMuenzeEin(float wert);
    float gesamtWert() const;
    void leeren();
};

#endif
