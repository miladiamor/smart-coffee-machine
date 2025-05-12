#pragma once
#include "TankTyp.h"

class Behaelter {
private:
    TankTyp typ;
    int gewicht_g;

public:
    Behaelter(TankTyp typ, int gewicht);
    int gewichtPruefen() const;
    TankTyp getTyp() const;
};
