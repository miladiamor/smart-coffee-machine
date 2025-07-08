#pragma once

#include "Muenzroehrenspeicher.h"
#include "MuenzEingabeSensor.h"
#include "MuenzAuswerfer.h"
#include "Display.h"

class Zahlungseinheit {
private:
    bool zahlungAktiv = false;
    bool zahlungErfolgreich = false;
    float gesamterEinwurf = 0.0f;
    float preis = 0.0f;

    Muenzroehrenspeicher* speicherVerwaltung = nullptr;
    MuenzEingabeSensor* sensor = nullptr;
    MuenzAuswerfer* auswerfer = nullptr;
    Display* display = nullptr;

public:

    Zahlungseinheit();


    Zahlungseinheit(Muenzroehrenspeicher* speicherVerwaltung,
                    MuenzEingabeSensor* sensor,
                    MuenzAuswerfer* auswerfer);


    bool getZahlungErfolgreich();


    void versucheZahlung(float preis);


    void zahlungAbbrechen();


    void tick();


    void setDisplay(Display* display);
    void setTestZahlungAktiv(bool aktiv);
};
