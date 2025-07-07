#pragma once

#include "Muenzroehrenspeicher.h"
#include "MuenzEingabeSensor.h"
#include "MuenzAuswerfer.h"
#include "Produkt.h"

class Zahlungseinheit {
private:
    enum ZahlungsState {
        ZAHLUNG_IDLE,         // Kein aktiver Zahlungsvorgang
        ZAHLUNG_LAEUFT,       // Zahlung ist aktiv
        ZAHLUNG_ERFOLGREICH,  // Zahlung abgeschlossen
        ZAHLUNG_ABORT         // Zahlung abgebrochen
    };

    ZahlungsState state = ZAHLUNG_IDLE;   // aktueller Zustand
    bool zahlungAktiv = false;            // ob Zahlung laeuft
    float gesamterEinwurf = 0.0f;         // bisher eingeworfener Betrag
    float preis;
    Muenzroehrenspeicher* roehren;
    MuenzEingabeSensor* eingabe;
    MuenzAuswerfer* auswerfer;

public:
    Zahlungseinheit();  // Standardkonstruktor fuer Unittests
    Zahlungseinheit(Muenzroehrenspeicher* roehren,
                    MuenzEingabeSensor* eingabe,
                    MuenzAuswerfer* auswerfer);

    bool versucheZahlung(float preis);  // Startet Zahlung
    void zahlungAbbrechen();                 // Bricht Zahlung ab
    void tick();                             // Zustandsbasierte Ausfuehrung
};
