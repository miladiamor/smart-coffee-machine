#pragma once
#include "TankTyp.h"

class Tankwaage {
private:
    TankTyp typ;
    int gewicht_g;
    static constexpr int MINDESTMENGE_G = 50;

    bool milchHatGenug(int menge_g) const;

public:
    Tankwaage(TankTyp typ, int gewicht);

    int gewichtPruefen() const;
    TankTyp getTyp() const;

    bool istLeer() const;
    bool hatGenug(int menge) const;
    bool entnehmen(int menge);
};
