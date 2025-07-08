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
    Muenzroehre* ziel = nullptr;

    // Passende Röhre je nach Muenzwert auswaehlen
    if (wert == 2.0f) ziel = roehre2Euro;
    else if (wert == 1.0f) ziel = roehre1Euro;
    else if (wert == 0.5f) ziel = roehre50Cent;
    else if (wert == 0.2f) ziel = roehre20Cent;
    else if (wert == 0.1f) ziel = roehre10Cent;
    else {
        // Ungueltiger Muenzwert wird direkt wieder ausgeworfen
        if (auswerfer) auswerfer->auswerfenMuenze(wert);
        return false;
    }

    // Wenn das Zielrohr nicht existiert oder voll ist dann Muenze auswerfen
    if (!ziel || ziel->istVoll()) {
        if (auswerfer) auswerfer->auswerfenMuenze(wert);
        return false;
    }

    // Gueltige Muenze in Roehre schieben
    if (schieber) schieber->schiebeMuenzeInRoehre(ziel);
    return true;
}

