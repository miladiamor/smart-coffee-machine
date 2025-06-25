
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

    // Schleife: Nutzer wirft Mnzen ein, bis Preis erreicht ist
    while (roehren->gesamtWert() < preis) {
        float muenzwert = eingabe->erkenneMuenze();

        if (eingabe->ungueltigeMuenze()) {
            auswerfer->auswerfenMuenze(muenzwert);
            continue;
        }

        if (!roehren->fuegeMuenzeEin(muenzwert)) {
            auswerfer->auswerfenMuenze(muenzwert);
        }
    }

    // Zahlung erfolgreich
    produkt->dekrementiereAnzahl();

    float rueckgeld = roehren->gesamtWert() - preis;
    if (rueckgeld > 0.0f) {
        auswerfer->auswerfen(rueckgeld);
    }

    return true;
}

void Zahlungseinheit::zahlungAbbrechen() {
    // Gibt aktuellen Betrag im Speicher als Rckgeld aus
    auswerfer->auswerfen(roehren->gesamtWert());
}
