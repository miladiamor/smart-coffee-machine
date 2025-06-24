#pragma once
#include "Heizelemente.h"
#include "Temperatursensor.h"
class Heizregler {

public:
    Heizregler();
    ~Heizregler();

    bool getEingeschaltet();
    void temperaturRegeln(int zieltemperatur_Cel);
    bool istTemperaturErreicht() const;
    void updateTemperatur();

private:
    bool eingeschaltet;
    int zieltemperatur_Cel;
    int aktuelleTemperatur_Cel;
    Temperatursensor *sensor;
    Heizelemente *heizen;   
};

