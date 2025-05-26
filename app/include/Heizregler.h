#pragma once
#include "Heizelemente.h"
#include "Temperatursensor.h"
class Heizregler {

private:
    bool eingeschaltet;
    int zieltemperatur_Cel;
    Temperatursensor *sensor;
    Heizelemente *heizen;
    //void einschalten();
    //void ausschalten();

public:
    Heizregler();

    bool getEingeschaltet();
    void temperaturRegeln(int zieltemperatur_Cel);
    //void regelnStoppen();

    
};

