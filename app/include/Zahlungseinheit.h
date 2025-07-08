#pragma once

#include "Muenzroehrenspeicher.h"
#include "MuenzEingabeSensor.h"
#include "MuenzAuswerfer.h"
#include "display.h"

class Zahlungseinheit {
private:
    bool zahlungAktiv;
    bool zahlungErfolgreich;        // ob Zahlung laeuft
    float gesamterEinwurf;         // bisher eingeworfener Betrag
    float preis;
    Muenzroehrenspeicher* speicherVerwaltung;
    MuenzEingabeSensor* sensor;
    MuenzAuswerfer* auswerfer;
    Display *display;
public:
    Zahlungseinheit();  // Standardkonstruktor fuer Unittests
    Zahlungseinheit(Muenzroehrenspeicher* speicherVerwaltung,
                    MuenzEingabeSensor* sensor,
                    MuenzAuswerfer* auswerfer);
    bool getZahlungErfolgreich();
    void versucheZahlung(float preis);  // Startet Zahlung
    void zahlungAbbrechen();                 // Bricht Zahlung ab
    void tick();                             // Zustandsbasierte Ausfuehrung

    void setDisplay(Display *display);
};
