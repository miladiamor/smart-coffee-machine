#include "Temperatursensor.h"

Temperatursensor::Temperatursensor(){
}

int Temperatursensor::getTemperatur_Cel(){
    return temperatur_Cel;
}

void Temperatursensor::setTemperatur_Cel(int t_cel) {
    this->temperatur_Cel = t_cel;
}
