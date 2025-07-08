#include "Muenzroehrenspeicher.h"

//Konstruktor fuer Unittests
Muenzroehrenspeicher::Muenzroehrenspeicher()
    : roehre2Euro(nullptr), roehre1Euro(nullptr), roehre50Cent(nullptr),
    roehre20Cent(nullptr), roehre10Cent(nullptr),
    schieber(nullptr), auswerfer(nullptr) {}


Muenzroehrenspeicher::Muenzroehrenspeicher(Muenzroehre* r2, Muenzroehre* r1, Muenzroehre* r50,
                                           Muenzroehre* r20, Muenzroehre* r10,
                                           Muenzenschieber* schieber, MuenzAuswerfer* auswerfer)
    : roehre2Euro(r2), roehre1Euro(r1), roehre50Cent(r50),
    roehre20Cent(r20), roehre10Cent(r10),
    schieber(schieber), auswerfer(auswerfer) {}



// Gibt false zurueck, wenn Muenze ungueltig oder Zielrohr voll ist.
bool Muenzroehrenspeicher::fuegeMuenzeEin(float wert) {
    return true;
}

void Muenzroehrenspeicher::tick() {
}
