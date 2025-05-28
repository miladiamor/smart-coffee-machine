#ifndef ZAHLUNGSEINHEIT_H
#define ZAHLUNGSEINHEIT_H

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
    Zahlungseinheit(Muenzroehrenspeicher* roehren,
                    MuenzEingabeSensor* eingabe,
                    MuenzAuswerfer* auswerfer);

    bool versucheZahlung(Produkt* produkt);
    void zahlungAbbrechen();
};

#endif // ZAHLUNGSEINHEIT_H

