#include "Temperatursensor.h"

Temperatursensor::Temperatursensor(){
    temperatur_Cel = 22;
}

int Temperatursensor::getTemperatur_Cel(){
    return temperatur_Cel;
}
