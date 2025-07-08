#include "Zahlungseinheit.h"
#include <cmath>
#include <QDebug>

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
        qDebug() << "Zahlung aktiv!";
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
    if (!zahlungAktiv) {return;}
    if (sensor->getMuenzeGueltig()) {
        float eingeworfeneMuenze = sensor->getEingeworfeneMuenze();
        if (!speicherVerwaltung->fuegeMuenzeEin(eingeworfeneMuenze)) {zahlungAktiv = false; return;}
        gesamterEinwurf -= eingeworfeneMuenze;
        qDebug() << "Rest: " << gesamterEinwurf;
        if (gesamterEinwurf == 0) {
            zahlungErfolgreich = true;
            zahlungAktiv = false;
            qDebug() << "Zahlung erfolgreich";
            return;
        } else if (gesamterEinwurf < 0) {
            float rueckgeld = std::abs(gesamterEinwurf);
            speicherVerwaltung->geldAuswerfen(rueckgeld);
            zahlungErfolgreich = true;
            zahlungAktiv = false;
            qDebug() << "Zahlung erfolgreich mit rückgeld";
            return;
        }

        QString ausgabe = QStringLiteral("Zu bezahlen: %1 EUR").arg(gesamterEinwurf, 'f', 2);
        qDebug() << "Ausgabe: " << ausgabe;
        display->displayText(ausgabe);
    }
}

void Zahlungseinheit::setDisplay(Display *display) {
    this->display = display;
}
