#include "zahlungseinheit.h"

// ich habe das addiert um ein problem in meinen test yu loeschen
Zahlungseinheit::Zahlungseinheit() {
    roehren = nullptr;
    eingabe = nullptr;
    auswerfer = nullptr;
    produkt = nullptr;
}

Zahlungseinheit::Zahlungseinheit(Muenzroehrenspeicher* roehren,
                                 MuenzEingabeSensor* eingabe,
                                 MuenzAuswerfer* auswerfer)
    : roehren(roehren), eingabe(eingabe), auswerfer(auswerfer), produkt(nullptr) {}

bool Zahlungseinheit::versucheZahlung(Produkt* produkt) {
    if (!produkt || produkt->getPreis() <= 0.0f || produkt->getAnzahl() <= 0) {
        return false;
    }

    this->produkt = produkt;
    float preis = produkt->getPreis();
    float gesamterEinwurf = 0.0f;

    while (gesamterEinwurf < preis) {
        float muenzwert = eingabe->getEingeworfeneMuenze();

        if (!roehren->fuegeMuenzeEin(muenzwert)) {
            auswerfer->auswerfenMuenze(muenzwert);
        } else {
            gesamterEinwurf += muenzwert;
        }

        break;
    }

    /*
    if (gesamterEinwurf < preis) {
        return false;
    }
    */

    produkt->dekrementiereAnzahl();

    float rueckgeld = gesamterEinwurf - preis;
    if (rueckgeld > 0.0f) {
        auswerfer->auswerfen(rueckgeld);
    }

    return true;
}

void tick() {
    // prüfen ob eine zahlung aktiv ist
    // prüfen ob eine Münze eingeworfen wurde und ob sie valide ist
    // prüfen welche münze eingeworfen wurde
    // Muenzspeicher-counter für diese münze um 1 erhöhen
    // Muenze in Rohr schieben
    // zu zahlenden betrag ob münz wert reduzieren
    // wenn mehr geld eingeworfen wurde als zu bezahlen
    // bool zahlung erfoglreich setzen
    // rückgeld ausgeben wenn nötig
}
void Zahlungseinheit::zahlungAbbrechen() {
    auswerfer->auswerfen(roehren->gesamtWert());
}
