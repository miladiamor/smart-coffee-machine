#include "Behaelter.h"

Behaelter::Behaelter(TankTyp typ, int gewicht)
    : typ(typ), gewicht_g(gewicht) {}

int Behaelter::gewichtPruefen() const {
    return gewicht_g;
}

TankTyp Behaelter::getTyp() const {
    return typ;
}
