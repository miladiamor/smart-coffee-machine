#include "Zahlungseinheit.h"
#include <cmath>
#include <QDebug>

bool Zahlungseinheit::getZahlungErfolgreich()
{
    bool ret = false;
    if (zahlungErfolgreich) {ret = true; zahlungErfolgreich = false;}
    return ret;
}

// Initialisiert die Zahlung fuer ein Produkt
void Zahlungseinheit::versucheZahlung(float preis) {
    if (!zahlungAktiv) {
        gesamterEinwurf = preis;
        this->preis = preis;
        zahlungAktiv = true;
        QString ausgabe = QStringLiteral("Zu bezahlen: %1 EUR").arg(gesamterEinwurf, 0, 'f', 2);
        qDebug() << "DEBUG: ausgabe " << ausgabe;
        display->displayText(ausgabe);
        qDebug() << "Zahlung aktiv!";
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
        if ((gesamterEinwurf >= -0.005f) && (gesamterEinwurf <= 0.005f)) {
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

        QString ausgabe = QStringLiteral("Zu bezahlen: %1 EUR").arg(gesamterEinwurf, 0, 'f', 2);
        qDebug() << "Ausgabe: " << ausgabe;
        display->displayText(ausgabe);
    }
}

void Zahlungseinheit::setDisplay(Display *display) {
    this->display = display;
}
