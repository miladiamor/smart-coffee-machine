#include "Behaelter.h"

Behaelter::Behaelter(TankTyp typ, int gewicht)
    : typ(typ), gewicht_g(gewicht) {}

int Behaelter::gewichtPruefen() const {
    return gewicht_g;
}

TankTyp Behaelter::getTyp() const {
    return typ;
}

bool Behaelter::istLeer() const {
    return gewicht_g < MINDESTMENGE_G;
}

bool Behaelter::milchHatGenug(int menge_g) const {
    double benoetigt_ml = static_cast<double>(menge_g) / 1.03;
    double verfuegbar_ml = static_cast<double>(gewicht_g) / 1.03;
    return static_cast<int>(verfuegbar_ml) >= static_cast<int>(benoetigt_ml);
}

bool Behaelter::hatGenug(int menge) const {
    if (typ == TankTyp::milch) {
        return milchHatGenug(menge);
    }
    return gewicht_g >= menge;
}

bool Behaelter::entnehmen(int menge) {
    if (typ == TankTyp::milch) {
        if (milchHatGenug(menge)) {
            gewicht_g -= menge;
            return true;
        }
    } else if (gewicht_g >= menge) {
        gewicht_g -= menge;
        return true;
    }

    return false;
}
