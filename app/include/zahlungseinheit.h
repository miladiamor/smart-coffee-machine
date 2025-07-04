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
    bool zahlungAktiv = false;            // ob Zahlung läuft
    float gesamterEinwurf = 0.0f;         // eingeworfener Betrag

    Muenzroehrenspeicher* roehren;
    MuenzEingabeSensor* eingabe;
    MuenzAuswerfer* auswerfer;
    Produkt* produkt;

public:
    Zahlungseinheit();
    Zahlungseinheit(Muenzroehrenspeicher* roehren,
                    MuenzEingabeSensor* eingabe,
                    MuenzAuswerfer* auswerfer);

    bool versucheZahlung(Produkt* produkt);
    void zahlungAbbrechen();
    void tick();  // zustandsbasierter Ablauf
};
