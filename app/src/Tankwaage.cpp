#include "Tankwaage.h"

Tankwaage::Tankwaage(TankTyp typ, int gewicht)
    : typ(typ), gewicht_g(gewicht) {}

int Tankwaage::gewichtPruefen() const {
    return gewicht_g;
}

TankTyp Tankwaage::getTyp() const {
    return typ;
}

void Tankwaage::reduziereGewicht(int g) {
    gewicht_g -= g;
    if (gewicht_g < 0) gewicht_g = 0;
}
