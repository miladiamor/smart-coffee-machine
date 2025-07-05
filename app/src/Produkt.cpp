#include "Produkt.h"

Produkt::Produkt()
    : name(""), preis(0.0f), anzahl(0) {}

Produkt::Produkt(std::string name, float preis, int anzahl)
    : name(name), preis(preis), anzahl(anzahl) {}

std::string Produkt::getName() const {
    return name;
}

float Produkt::getPreis() const {
    return preis;
}

int Produkt::getAnzahl() const {
    return anzahl;
}

void Produkt::dekrementiereAnzahl() {
    if (anzahl > 0) {
        anzahl--;
    }
}
