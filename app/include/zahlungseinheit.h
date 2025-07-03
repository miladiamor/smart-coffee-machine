#pragma once

#include "Muenzroehrenspeicher.h"
#include "MuenzEingabeSensor.h"
#include "MuenzAuswerfer.h"
#include "Produkt.h"

class Zahlungseinheit {
private:
    Muenzroehrenspeicher* roehren;
    MuenzEingabeSensor* eingabe;
    MuenzAuswerfer* auswerfer;
    Produkt* produkt;

public:
    Zahlungseinheit();  // ich habe das addiert um ein problem in meinen test yu loeschen
    Zahlungseinheit(Muenzroehrenspeicher* roehren,
                    MuenzEingabeSensor* eingabe,
                    MuenzAuswerfer* auswerfer);

    bool versucheZahlung(Produkt* produkt);
    void zahlungAbbrechen();
};
