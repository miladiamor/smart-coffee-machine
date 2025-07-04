#include "zahlungseinheit.h"

// leerer Konstruktor fuer Unit-Tests
Zahlungseinheit::Zahlungseinheit() {
    roehren = nullptr;
    eingabe = nullptr;
    auswerfer = nullptr;
    produkt = nullptr;
    gesamterEinwurf = 0.0f;
    state = ZAHLUNG_IDLE;
    zahlungAktiv = false;
}

Zahlungseinheit::Zahlungseinheit(Muenzroehrenspeicher* roehren,
                                 MuenzEingabeSensor* eingabe,
                                 MuenzAuswerfer* auswerfer)
    : roehren(roehren), eingabe(eingabe), auswerfer(auswerfer),
    produkt(nullptr), gesamterEinwurf(0.0f),
    state(ZAHLUNG_IDLE), zahlungAktiv(false) {}

bool Zahlungseinheit::versucheZahlung(Produkt* produkt) {
    if (!produkt || produkt->getPreis() <= 0.0f || produkt->getAnzahl() <= 0) {
        return false;
    }

    this->produkt = produkt;
    gesamterEinwurf = 0.0f;
    state = ZAHLUNG_LAEUFT;
    zahlungAktiv = true;

    return true;
}

void Zahlungseinheit::tick() {
    // pruefen ob eine zahlung aktiv ist
    if (!zahlungAktiv || !produkt || state != ZAHLUNG_LAEUFT)
        return;

    // pruefen ob eine muenze eingeworfen wurde
    float muenzwert = eingabe->getEingeworfeneMuenze();
    if (muenzwert <= 0.0f)
        return;

    // pruefen ob sie gueltig ist
    if (eingabe->istUngueltigeMuenze()) {
        auswerfer->auswerfenMuenze(muenzwert);
        return;
    }

    // muenze in speicher einfuegen
    if (!roehren->fuegeMuenzeEin(muenzwert)) {
        auswerfer->auswerfenMuenze(muenzwert);
        return;
    }

    gesamterEinwurf += muenzwert;

    float preis = produkt->getPreis();
    if (gesamterEinwurf >= preis) {
        float rueckgeld = gesamterEinwurf - preis;
        if (rueckgeld > 0.0f) {
            auswerfer->auswerfen(rueckgeld);
        }

        produkt->dekrementiereAnzahl();
        state = ZAHLUNG_ERFOLGREICH;
        zahlungAktiv = false;
    }
}

void Zahlungseinheit::zahlungAbbrechen() {
    if (zahlungAktiv) {
        auswerfer->auswerfen(gesamterEinwurf);
        gesamterEinwurf = 0.0f;
        zahlungAktiv = false;
        state = ZAHLUNG_IDLE;
    }
}
