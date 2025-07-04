#include "Muenzroehrenspeicher.h"
#include "Muenzenschieber.h"

Muenzroehrenspeicher::Muenzroehrenspeicher(Muenzroehre* r2, Muenzroehre* r1, Muenzroehre* r50,
                                           Muenzroehre* r20, Muenzroehre* r10,
                                           Muenzenschieber* schieber, MuenzAuswerfer* auswerfer)
    : roehre2Euro(r2), roehre1Euro(r1), roehre50Cent(r50),
    roehre20Cent(r20), roehre10Cent(r10),
    schieber(schieber), auswerfer(auswerfer) {}

bool Muenzroehrenspeicher::fuegeMuenzeEin(float wert) {
    if (wert == 50) {muenzen[50] += 1;}

    Muenzroehre* ziel = nullptr;

    if (wert == 2.0f) ziel = roehre2Euro;
    else if (wert == 1.0f) ziel = roehre1Euro;
    else if (wert == 0.5f) ziel = roehre50Cent;
    else if (wert == 0.2f) ziel = roehre20Cent;
    else if (wert == 0.1f) ziel = roehre10Cent;
    else {
        auswerfer->auswerfenMuenze(wert);
        return false;
    }

    if (ziel->istVoll()) {
        auswerfer->auswerfenMuenze(wert);
        return false;
    }

    schieber->schiebeMuenzeInRoehre(ziel);
    return true;
}

float Muenzroehrenspeicher::gesamtWert() const {
    return 2.0f * roehre2Euro->getAktuelleAnzahl() +
           1.0f * roehre1Euro->getAktuelleAnzahl() +
           0.5f * roehre50Cent->getAktuelleAnzahl() +
           0.2f * roehre20Cent->getAktuelleAnzahl() +
           0.1f * roehre10Cent->getAktuelleAnzahl();
}

void Muenzroehrenspeicher::leeren() {
    roehre2Euro->leeren();
    roehre1Euro->leeren();
    roehre50Cent->leeren();
    roehre20Cent->leeren();
    roehre10Cent->leeren();
}

Muenzroehrenspeicher::Muenzroehrenspeicher() {
    // Leerer Dummy Konstruktor fuer unittest
    roehre2Euro = nullptr;
    roehre1Euro = nullptr;
    roehre50Cent = nullptr;
    roehre20Cent = nullptr;
    roehre10Cent = nullptr;
    schieber = nullptr;
    auswerfer = nullptr;
}
