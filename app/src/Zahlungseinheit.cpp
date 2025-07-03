#include "zahlungseinheit.h"

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

    if (gesamterEinwurf < preis) {
        return false;
    }

    produkt->dekrementiereAnzahl();

    float rueckgeld = gesamterEinwurf - preis;
    if (rueckgeld > 0.0f) {
        auswerfer->auswerfen(rueckgeld);
    }

    return true;
}

void Zahlungseinheit::zahlungAbbrechen() {
    auswerfer->auswerfen(roehren->gesamtWert());
}
