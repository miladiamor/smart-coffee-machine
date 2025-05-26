#pragma once
#include "TankTyp.h"

class Tankwaage {
private:
    float gewicht_g;

public:
    Tankwaage(float gewicht_g);

    float gewichtPruefen() const;
    void setGewicht_g(float gewicht_g)
};
