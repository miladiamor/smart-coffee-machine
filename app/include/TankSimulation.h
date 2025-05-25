#pragma once
#include "Tankwaage.h"

class TankSimulation {
public:
    static bool hatGenug(const Tankwaage& tank, int menge);
    static bool entnehmen(Tankwaage& tank, int menge);
};
