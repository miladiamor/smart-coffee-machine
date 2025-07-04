#include "Zahlungseinheit.h"

// Konstruktor ohne Parameter fuer Unittests
Zahlungseinheit::Zahlungseinheit() {
    roehren = nullptr;
    eingabe = nullptr;
    auswerfer = nullptr;
    produkt = nullptr;
    gesamterEinwurf = 0.0f;
    state = ZAHLUNG_IDLE;
    zahlungAktiv = false;
}

// Konstruktor mit Abhaengigkeiten
Zahlungseinheit::Zahlungseinheit(Muenzroehrenspeicher* roehren,
                                 MuenzEingabeSensor* eingabe,
                                 MuenzAuswerfer* auswerfer)
    : roehren(roehren), eingabe(eingabe), auswerfer(auswerfer),
    produkt(nullptr), gesamterEinwurf(0.0f),
    state(ZAHLUNG_IDLE), zahlungAktiv(false) {}

// Initialisiert die Zahlung fuer ein Produkt
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

// Fuehrt einen Tick aus: verarbeitet eine Muenze
void Zahlungseinheit::tick() {
    if (!zahlungAktiv || !produkt || state != ZAHLUNG_LAEUFT)
        return;

    float muenzwert = eingabe->getEingeworfeneMuenze();
    if (muenzwert <= 0.0f)
        return;

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

// Bricht den Zahlungsvorgang ab und gibt Geld zurueck
void Zahlungseinheit::zahlungAbbrechen() {
    if (zahlungAktiv) {
        auswerfer->auswerfen(gesamterEinwurf);
        gesamterEinwurf = 0.0f;
        zahlungAktiv = false;
        state = ZAHLUNG_IDLE;
    }
}
