#pragma once
#include "TankTyp.h"
#include "Gewicht.h"

class Behaelter {
private:
    TankTyp typ;
    Gewicht gewicht;

public:
    Behaelter(TankTyp typ);
    int gewichtPruefen() const;
    TankTyp getTyp() const;
};

