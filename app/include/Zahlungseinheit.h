#pragma once

#include "Muenzroehrenspeicher.h"
#include "MuenzEingabeSensor.h"
#include "MuenzAuswerfer.h"

class Zahlungseinheit {
private:
    bool zahlungAktiv;
    bool zahlungErfolgreich;        // ob Zahlung laeuft
    float gesamterEinwurf;         // bisher eingeworfener Betrag
    float preis;
    Muenzroehrenspeicher* roehren;
    MuenzEingabeSensor* eingabe;
    MuenzAuswerfer* auswerfer;

public:
    Zahlungseinheit();  // Standardkonstruktor fuer Unittests
    Zahlungseinheit(Muenzroehrenspeicher* roehren,
                    MuenzEingabeSensor* eingabe,
                    MuenzAuswerfer* auswerfer);

    void getZahlungErfolgreich();
    void versucheZahlung(float preis);  // Startet Zahlung
    void zahlungAbbrechen();                 // Bricht Zahlung ab
    void tick();                             // Zustandsbasierte Ausfuehrung
};
