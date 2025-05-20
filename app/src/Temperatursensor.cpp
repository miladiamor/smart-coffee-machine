#include "Temperatursensor.h"

Temperatursensor::Temperatursensor(){
    temperatur_Cel = 22; // Default Temp
}

int Temperatursensor::getTemperatur_Cel(){  // Methode implementierung
    return temperatur_Cel;
}
