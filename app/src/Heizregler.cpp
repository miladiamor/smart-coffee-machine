#include "Heizregler.h"
#include "qdebug.h"

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

void Heizregler::setHeizelement(Heizelemente *heizelement)
{
    this->heizen = heizelement;
}

void Heizregler::setTemperatursensor(Temperatursensor *temperatursensor)
{
    this->sensor = temperatursensor;
}

bool Heizregler::getEingeschaltet() {
    return eingeschaltet;
}

void Heizregler::tick(){
    if (eingeschaltet){
        qDebug() << "1";
        if (istTemperaturErreicht()){
            eingeschaltet = false;
             qDebug() << "2";
            heizen->ausschalten();
              qDebug() << "3";
        } else{
            heizen->einschalten();
        }
    }
}



