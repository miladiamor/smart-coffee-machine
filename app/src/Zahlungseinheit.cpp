#include "Zahlungseinheit.h"
#include <cmath>

// Konstruktor ohne Parameter fuer Unittests
Zahlungseinheit::Zahlungseinheit() {
    sensor = nullptr;
    speicherVerwaltung = nullptr;
    auswerfer = nullptr;
    gesamterEinwurf = 0.0f;
    zahlungAktiv = false;
}

// Konstruktor mit Abhaengigkeiten
Zahlungseinheit::Zahlungseinheit(Muenzroehrenspeicher* speicherVerwaltung,
                                 MuenzEingabeSensor* sensor,
                                 MuenzAuswerfer* auswerfer)
    : zahlungAktiv(false), gesamterEinwurf(0.0f),
    speicherVerwaltung(speicherVerwaltung),
    sensor(sensor), auswerfer(auswerfer) {}

// Initialisiert die Zahlung fuer ein Produkt
void Zahlungseinheit::versucheZahlung(float preis) {
    if (!zahlungAktiv) {
        gesamterEinwurf = preis;
        this->preis = preis;
        zahlungAktiv = true;
    }
}

// Fuehrt einen Tick aus: verarbeitet eine Muenze
void Zahlungseinheit::tick() {
    if (zahlungAktiv) {return;}
    if (!sensor->getMuenzeGueltig()) {return;}

    float eingeworfeneMuenze = sensor->getEingeworfeneMuenze();
    if (!speicherVerwaltung->fuegeMuenzeEin(eingeworfeneMuenze)) {zahlungAktiv = false; return;}

    gesamterEinwurf -= eingeworfeneMuenze;
    if (gesamterEinwurf == 0) {
        zahlungErfolgreich = true;
        zahlungAktiv = false;
        return;
    } else if (gesamterEinwurf < 0) {
        float rueckgeld = std::abs(gesamterEinwurf);
        speicherVerwaltung->geldAuswerfen(rueckgeld);
        zahlungErfolgreich = true;
        zahlungAktiv = false;
    }

    display->displayText(QStringLiteral("Zu bezahlen: %1 €").arg(gesamterEinwurf, 0, 'f', 2));
}

void Zahlungseinheit::setDisplay(Display *display) {
    this->display = display;
}

