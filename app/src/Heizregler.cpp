#include "Heizregler.h"
#include <QDebug>

Heizregler::Heizregler() {
    heizen = new Heizelemente();
    sensor = new Temperatursensor();
}

bool Heizregler::getEingeschaltet(){
    return this->eingeschaltet;
}

void Heizregler::temperaturRegeln(int zieltemperatur_Cel) {
    this->zieltemperatur_Cel = zieltemperatur_Cel;
    heizen->einschalten();
    while((eingeschaltet == true) && (sensor->getTemperatur_Cel() < zieltemperatur_Cel)) {}
    heizen->ausschalten();

}

