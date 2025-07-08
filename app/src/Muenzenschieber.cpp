#include "Muenzenschieber.h"

Muenzenschieber::Muenzenschieber()
    : aktiveMuenzroehre(nullptr) {}  // Initialisiert auf nullptr

void Muenzenschieber::schiebeMuenzeInRoehre(Muenzroehre* muenzroehre) {
    aktiveMuenzroehre = muenzroehre;  //  Speichert die Referenz
    aktiveMuenzroehre->erhoeheAnzahl();
    sensor->setEingeworfeneMuenze(0.0);
}
