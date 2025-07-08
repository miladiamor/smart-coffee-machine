#include "Zahlungseinheit.h"
#include <cmath>

// Konstruktor ohne Parameter fuer Unittests
Zahlungseinheit::Zahlungseinheit() {
    sensor = nullptr;
    speicherVerwaltung = nullptr;
    auswerfer = nullptr;
    gesamterEinwurf = 0.0f;
    zahlungAktiv = false;
    zahlungErfolgreich = false;

}

// Konstruktor mit Abhaengigkeiten
Zahlungseinheit::Zahlungseinheit(Muenzroehrenspeicher* speicherVerwaltung,
                                 MuenzEingabeSensor* sensor,
                                 MuenzAuswerfer* auswerfer)
    : zahlungAktiv(false),
    zahlungErfolgreich(false),
    gesamterEinwurf(0.0f),
    preis(0.0f),
    speicherVerwaltung(speicherVerwaltung),
    sensor(sensor),
    auswerfer(auswerfer),
    display(nullptr)
{}

bool Zahlungseinheit::getZahlungErfolgreich()
{
    return zahlungErfolgreich;
}

// Initialisiert die Zahlung fuer ein Produkt
void Zahlungseinheit::versucheZahlung(float preis) {
    if (!zahlungAktiv) {
        gesamterEinwurf = preis;
        this->preis = preis;
        zahlungAktiv = true;
    }
}
void Zahlungseinheit::setTestZahlungAktiv(bool aktiv) {
    zahlungAktiv = aktiv;
}

void Zahlungseinheit::setMuenzroehrenspeicher(Muenzroehrenspeicher *muenzroehrenspeicher)
{
    this->speicherVerwaltung = muenzroehrenspeicher;
}

void Zahlungseinheit::setMuenzEingabeSensor(MuenzEingabeSensor *muenzeingabesensor)
{
    this->sensor = muenzeingabesensor;
}

void Zahlungseinheit::setMuenzAuswerfer(MuenzAuswerfer *muenzauswerfer)
{
    this->auswerfer = muenzauswerfer;
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
