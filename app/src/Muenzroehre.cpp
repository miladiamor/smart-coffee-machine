#include "Muenzroehre.h"

Muenzroehre::Muenzroehre(int kapazitaet)
    : kapazitaet(kapazitaet), aktuelleAnzahl(0) {}


Muenzroehre::Muenzroehre(int kapazitaet)
    : kapazitaet(kapazitaet), aktuelleAnzahl(0) {}

bool Muenzroehre::istVoll() const {
    return aktuelleAnzahl >= kapazitaet;
}

void Muenzroehre::leeren() {
    aktuelleAnzahl = 0;
}

int Muenzroehre::getAktuelleAnzahl() const {
    return aktuelleAnzahl;
}

int Muenzroehre::getKapazitaet() const {
    return kapazitaet;
}

void Muenzroehre::erhoeheAnzahl() {
    if (!istVoll()) {
        aktuelleAnzahl++;
    }
}
