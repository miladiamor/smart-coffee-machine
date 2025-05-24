#include "Tankwaage.h"

Tankwaage::Tankwaage(TankTyp typ, int gewicht)
    : typ(typ), gewicht_g(gewicht) {}

int Tankwaage::gewichtPruefen() const {
    return gewicht_g;
}

TankTyp Tankwaage::getTyp() const {
    return typ;
}

bool Tankwaage::istLeer() const {
    return gewicht_g < MINDESTMENGE_G;
}

bool Tankwaage::milchHatGenug(int menge_g) const {
    constexpr double MILCH_DICHTE = 1.03;
    double benoetigt_ml = static_cast<double>(menge_g) / MILCH_DICHTE;
    double verfuegbar_ml = static_cast<double>(gewicht_g) / MILCH_DICHTE;
    return static_cast<int>(verfuegbar_ml) >= static_cast<int>(benoetigt_ml);
}

bool Tankwaage::hatGenug(int menge) const {
    if (typ == TankTyp::milch) {
        return milchHatGenug(menge);
    }
    return gewicht_g >= menge;
}

bool Tankwaage::entnehmen(int menge) {
    if (menge <= 0) return false;
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
