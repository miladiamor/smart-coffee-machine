#include "Heizregler.h"
#include <QDebug>

Heizregler::Heizregler() :
    eingeschaltet(false),
    zieltemperatur_Cel(0),
    aktuelleTemperatur_Cel(20),
    sensor(new Temperatursensor()),
    heizen(new Heizelemente())
{}

Heizregler::~Heizregler(){
    delete sensor;
    delete heizen;
}

void Heizregler::temperaturRegeln(int zieltemperatur_Cel) {
    if(!eingeschaltet && zieltemperatur_Cel > aktuelleTemperatur_Cel){
    this->zieltemperatur_Cel = zieltemperatur_Cel;
    this->eingeschaltet = true;
    this->heizen->einschalten();
    }
}

bool Heizregler::istTemperaturErreicht() const {
    return (aktuelleTemperatur_Cel >= zieltemperatur_Cel);
}

void Heizregler::tick(){
    if (eingeschaltet){
        if (istTemperaturErreicht()){
            eingeschaltet = false;
            heizen->ausschalten();
        } else{
            aktuelleTemperatur_Cel++;
        }
    }
}



