#ifndef MUENZROEHRENSPEICHER_H
#define MUENZROEHRENSPEICHER_H

#include "Muenzroehre.h"
#include "Muenzschieber.h"
#include "MuenzAuswerfer.h"

class Muenzroehrenspeicher {
private:
    Muenzroehre* roehre2Euro;
    Muenzroehre* roehre1Euro;
    Muenzroehre* roehre50Cent;
    Muenzroehre* roehre20Cent;
    Muenzroehre* roehre10Cent;

    Muenzschieber* schieber;
    MuenzAuswerfer* auswerfer;

public:
    Muenzroehrenspeicher(Muenzroehre* r2, Muenzroehre* r1, Muenzroehre* r50,
                         Muenzroehre* r20, Muenzroehre* r10,
                         Muenzschieber* schieber, MuenzAuswerfer* auswerfer);

    bool fuegeMuenzeEin(float wert);
    float gesamtWert() const;
    void leeren();
};

#endif // MUENZROEHRENSPEICHER_H
