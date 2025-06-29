#include "Heizregler.h"

void Heizregler::temperaturRegeln(int zieltemperatur_Cel) {
    if(!eingeschaltet && zieltemperatur_Cel > aktuelleTemperatur_Cel){
    this->zieltemperatur_Cel = zieltemperatur_Cel;
    this->eingeschaltet = true;
    //if (heizen) heizen->einschalten();
    this->heizen->einschalten();
    }
}

bool Heizregler::istTemperaturErreicht() const {
    return (aktuelleTemperatur_Cel >= zieltemperatur_Cel);
}

bool Heizregler::getEingeschaltet() {
    return eingeschaltet;
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



