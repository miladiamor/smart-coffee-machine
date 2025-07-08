#include "Zahlungseinheit.h"

// Konstruktor ohne Parameter fuer Unittests
Zahlungseinheit::Zahlungseinheit() {
    roehren = nullptr;
    eingabe = nullptr;
    auswerfer = nullptr;
    gesamterEinwurf = 0.0f;
    zahlungAktiv = false;
}

// Konstruktor mit Abhaengigkeiten
Zahlungseinheit::Zahlungseinheit(Muenzroehrenspeicher* roehren,
                                 MuenzEingabeSensor* eingabe,
                                 MuenzAuswerfer* auswerfer)
    : zahlungAktiv(false), gesamterEinwurf(0.0f),
    roehren(roehren),
    eingabe(eingabe), auswerfer(auswerfer) {}

// Initialisiert die Zahlung fuer ein Produkt
bool Zahlungseinheit::versucheZahlung(float preis) {
    this->preis = preis;
    gesamterEinwurf = 0.0f;
    zahlungAktiv = true;

    return true;
}

// Fuehrt einen Tick aus: verarbeitet eine Muenze
void Zahlungseinheit::tick() {
    if (!zahlungAktiv)
        return;

    float muenzwert = eingabe->getEingeworfeneMuenze();
    if (muenzwert <= 0.0f)
        return;

    if (!roehren->fuegeMuenzeEin(muenzwert)) {
        auswerfer->auswerfenMuenze(muenzwert);
        return;
    }

    gesamterEinwurf += muenzwert;

    if (gesamterEinwurf >= preis) {
        float rueckgeld = gesamterEinwurf - preis;
        if (rueckgeld > 0.0f) {
            auswerfer->auswerfen(rueckgeld);
        }
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
