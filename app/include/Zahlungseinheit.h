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

<<<<<<< HEAD
    bool getZahlungErfolgreich();
=======

    void getzahnlungErfolgreicht();
    bool getZahlungErfolgreich();

    bool getZahlungErfolgreich();

>>>>>>> 9ef873f51ad04f65c13763a2deaca84e65a4f387
    void versucheZahlung(float preis);  // Startet Zahlung
    void zahlungAbbrechen();                 // Bricht Zahlung ab
    void tick();                             // Zustandsbasierte Ausfuehrung
};
