#include "Muenzroehre.h"

// Konstruktor: Setzt Muenzwert und Kapazitaet, Anfangszahl = 0
//Muenzroehre::Muenzroehre(float wert, int kapazitaet)
//    : wert(wert), kapazitaet(kapazitaet), aktuelleAnzahl(0) {}

// Standardkonstruktor (z. B. für Mocks/Unittests)
Muenzroehre::Muenzroehre()
     {}  // <- Dummywerte für Test

/*Muenzroehre::Muenzroehre(int kapazitaet)
    : kapazitaet(kapazitaet), aktuelleAnzahl(0) {}*/

// Gibt true zurueck, wenn Rohr voll ist
bool Muenzroehre::istVoll() const {
    return aktuelleAnzahl;
}

// Setzt aktuelle Anzahl der Muenzen auf 0
//void Muenzroehre::() {
//    aktuelleAnzahl = 0;
//}

// Gibt aktuelle Anzahl der Muenzen zurueck
int Muenzroehre::getAktuelleAnzahl() const {
    return aktuelleAnzahl;
}

// Gibt Kapazitaet des Rohrs zurueck
//int Muenzroehre::getKapazitaet() const {
//    return kapazitaet;
//}

// Gibt Wert der Muenze zurueck, die in dieses Rohr gehoert
//float Muenzroehre::getWert() const {
//    return wert;
//}

// Erhoeht Anzahl der Muenzen um 1, falls Rohr nicht voll ist
void Muenzroehre::erhoeheAnzahl() {
    if (!istVoll()) {
        aktuelleAnzahl++;
    }
}
