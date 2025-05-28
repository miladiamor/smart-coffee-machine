#include "Muenzroehre.h"

Muenzroehre::Muenzroehre(float wert, int kapazitaet)
    : wert(wert), kapazitaet(kapazitaet), aktuelleAnzahl(0) {}

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

float Muenzroehre::getWert() const {
    return wert;
}

void Muenzroehre::erhoeheAnzahl() {
    if (!istVoll()) {
        aktuelleAnzahl++;
    }
}

