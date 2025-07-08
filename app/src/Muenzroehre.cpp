#include "Muenzroehre.h"

Muenzroehre::Muenzroehre()
     {}

// Gibt true zurueck, wenn Rohr voll ist
bool Muenzroehre::istVoll() const {
    return aktuelleAnzahl;
}

// Gibt aktuelle Anzahl der Muenzen zurueck
int Muenzroehre::getAnzahl() const {
    return aktuelleAnzahl;
}

// Erhoeht Anzahl der Muenzen um 1, falls Rohr nicht voll ist
void Muenzroehre::erhoeheAnzahl() {
    if (!istVoll()) {
        aktuelleAnzahl++;
    }
}

void Muenzroehre::reduziereAnzahl() {
    aktuelleAnzahl--;
}
