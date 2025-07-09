#include "Heizregler.h"
#include "qdebug.h"

void Heizregler::temperaturRegeln(int zieltemperatur_Cel) {
    if(!eingeschaltet && zieltemperatur_Cel > aktuelleTemperatur_Cel){
    this->zieltemperatur_Cel = zieltemperatur_Cel;
    this->eingeschaltet = true;
    this->heizen->einschalten();
    }
}

void Heizregler::setHeizelement(Heizelemente *heizelement)
{
    this->heizen = heizelement;
}

void Heizregler::setTemperatursensor(Temperatursensor *temperatursensor)
{
    this->sensor = temperatursensor;
}

bool Heizregler::istTemperaturErreicht() const {
    return (aktuelleTemperatur_Cel >= zieltemperatur_Cel);
}

bool Heizregler::getEingeschaltet() {
    return eingeschaltet;
}

void Heizregler::tick(){
    aktuelleTemperatur_Cel = sensor->getTemperatur_Cel();
    if (eingeschaltet){
        if (istTemperaturErreicht()){
            eingeschaltet = false;
            heizen->ausschalten();
        } else{
            heizen->einschalten();
        }
    }
}



