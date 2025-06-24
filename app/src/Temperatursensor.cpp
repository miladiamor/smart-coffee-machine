#include "Temperatursensor.h"

Temperatursensor::Temperatursensor() : temperatur_Cel(20){}

int Temperatursensor::getTemperatur_Cel() const{
    return temperatur_Cel;
}

void Temperatursensor::setTemperatur_Cel(int t_cel) {
    this->temperatur_Cel = t_cel;
}
