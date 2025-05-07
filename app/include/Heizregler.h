#pragma once
#include "Heizelemente.h"
#include "Temperatursensor.h"
class Heizregler {
private:
    int zieltemperatur_Cel;
    Temperatursensor *sensor;
    Heizelemente *heizen;

public:
    Heizregler();

    void temperaturRegeln(int Zieltemperatur_Cel);
    void regelnStoppen();
    
};

