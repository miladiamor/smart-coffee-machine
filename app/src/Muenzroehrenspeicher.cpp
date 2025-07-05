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


// Gibt den gesamten Geldwert im Speicher zurueck
// Wenn ein Rohr nicht existiert dann gibt 0.0f zurück
float Muenzroehrenspeicher::gesamtWert() const {
    if (!roehre2Euro || !roehre1Euro || !roehre50Cent || !roehre20Cent || !roehre10Cent)
        return 0.0f;

    // Wert berechnen: Anzahl * Muenzwert
    return 2.0f * roehre2Euro->getAktuelleAnzahl() +
           1.0f * roehre1Euro->getAktuelleAnzahl() +
           0.5f * roehre50Cent->getAktuelleAnzahl() +
           0.2f * roehre20Cent->getAktuelleAnzahl() +
           0.1f * roehre10Cent->getAktuelleAnzahl();
}


//  Leert alle Roehren im Speicher
// Setzt Anzahl aller Münzen auf 0
void Muenzroehrenspeicher::leeren() {
    if (roehre2Euro) roehre2Euro->leeren();
    if (roehre1Euro) roehre1Euro->leeren();
    if (roehre50Cent) roehre50Cent->leeren();
    if (roehre20Cent) roehre20Cent->leeren();
    if (roehre10Cent) roehre10Cent->leeren();
}
