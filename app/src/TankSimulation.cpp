#include "TankSimulation.h"

bool TankSimulation::hatGenug(const Tankwaage& tank, int menge) {
    if (tank.getTyp() == TankTyp::milch) {
        double verfuegbar_ml = static_cast<double>(tank.gewichtPruefen()) / 1.03;
        return static_cast<int>(verfuegbar_ml) >= menge;
    } else if (tank.getTyp() == TankTyp::zucker) {
        return tank.gewichtPruefen() >= menge * 5;
    }
    return tank.gewichtPruefen() >= menge;
}

bool TankSimulation::entnehmen(Tankwaage& tank, int menge) {
    if (!hatGenug(tank, menge)) return false;

    int abziehen = menge;
    if (tank.getTyp() == TankTyp::milch) {
        abziehen = static_cast<int>(menge * 1.03);
    } else if (tank.getTyp() == TankTyp::zucker) {
        abziehen = menge * 5;
    }

    tank.reduziereGewicht(abziehen);
    return true;
}
