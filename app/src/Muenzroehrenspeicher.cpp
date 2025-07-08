#include "Muenzroehrenspeicher.h"

// Konstruktor fuer Unittests
Muenzroehrenspeicher::Muenzroehrenspeicher()
    : roehre2Euro(nullptr), roehre1Euro(nullptr), roehre50Cent(nullptr),
    roehre20Cent(nullptr), roehre10Cent(nullptr),
    schieber(nullptr), auswerfer(nullptr) {}

// Konstruktor mit allen Komponenten
Muenzroehrenspeicher::Muenzroehrenspeicher(Muenzroehre* r2, Muenzroehre* r1, Muenzroehre* r50,
                                           Muenzroehre* r20, Muenzroehre* r10,
                                           Muenzenschieber* schieber, MuenzAuswerfer* auswerfer)
    : roehre2Euro(r2), roehre1Euro(r1), roehre50Cent(r50),
    roehre20Cent(r20), roehre10Cent(r10),
    schieber(schieber), auswerfer(auswerfer) {}


// Gibt false zurueck, wenn Muenze ungueltig oder Zielrohr voll ist.
bool Muenzroehrenspeicher::fuegeMuenzeEin(float wert) {

    Muenzroehre* ziel = nullptr;

    if (wert == 2.0f) ziel = roehre2Euro;
    else if (wert == 1.0f) ziel = roehre1Euro;
    else if (wert == 0.5f) ziel = roehre50Cent;
    else if (wert == 0.2f) ziel = roehre20Cent;
    else if (wert == 0.1f) ziel = roehre10Cent;
    else {
        if (auswerfer) auswerfer->auswerfenMuenze(wert);
        return false;
    }

    if (!ziel || ziel->istVoll()) {
        if (auswerfer) auswerfer->auswerfenMuenze(wert);
        return false;
    }

    if (schieber) schieber->schiebeMuenzeInRoehre(ziel);
    ziel->erhoeheAnzahl();
    return true;
}


void Muenzroehrenspeicher::muenzeAuswerfen(float wert) {
    Muenzroehre* quelle = nullptr;

    if (wert == 2.0f) quelle = roehre2Euro;
    else if (wert == 1.0f) quelle = roehre1Euro;
    else if (wert == 0.5f) quelle = roehre50Cent;
    else if (wert == 0.2f) quelle = roehre20Cent;
    else if (wert == 0.1f) quelle = roehre10Cent;
    else return;

    if (quelle && quelle->getAktuelleAnzahl() > 0 && auswerfer) {
        quelle->verringereAnzahl();
        auswerfer->auswerfenMuenze(wert);
    }
}



void Muenzroehrenspeicher::geldAuswerfen(float betrag) {
    const float werte[] = {2.0f, 1.0f, 0.5f, 0.2f, 0.1f};

    for (float wert : werte) {
        Muenzroehre* quelle = nullptr;

        if (wert == 2.0f) quelle = roehre2Euro;
        else if (wert == 1.0f) quelle = roehre1Euro;
        else if (wert == 0.5f) quelle = roehre50Cent;
        else if (wert == 0.2f) quelle = roehre20Cent;
        else if (wert == 0.1f) quelle = roehre10Cent;

        while (betrag >= wert - 0.001f && quelle && quelle->getAktuelleAnzahl() > 0) {
            betrag -= wert;
            muenzeAuswerfen(wert);
        }
    }
    return true;
}

void Muenzroehrenspeicher::tick() {

}
