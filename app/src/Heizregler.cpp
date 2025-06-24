#include "Heizregler.h"
#include <QDebug>

Heizregler::Heizregler() {
    heizen = new Heizelemente();
    sensor = new Temperatursensor();
}

bool Heizregler::getEingeschaltet(){
    return this->eingeschaltet;
}

bool Heizregregler::temperaturErreicht() {

}

void Heizregler::temperaturRegeln(int zieltemperatur_Cel) {
    this->zieltemperatur_Cel = zieltemperatur_Cel;


}

