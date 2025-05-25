#pragma once
#include "TankTyp.h"

class Tankwaage {
private:
    TankTyp typ;
    int gewicht_g;

public:
    Tankwaage(TankTyp typ, int gewicht);

    int gewichtPruefen() const;
    TankTyp getTyp() const;
};
