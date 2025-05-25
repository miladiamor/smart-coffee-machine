#include "Tankwaage.h"

Tankwaage::Tankwaage(TankTyp typ, int gewicht)
    : typ(typ), gewicht_g(gewicht) {}

int Tankwaage::gewichtPruefen() const {
    return gewicht_g;
}

TankTyp Tankwaage::getTyp() const {
    return typ;
}
