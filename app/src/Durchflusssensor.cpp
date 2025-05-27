#include "Durchflusssensor.h"

Durchflusssensor::Durchflusssensor() :durchflussImpuls(false), impulsCount(0) {}

bool Durchflusssensor::getDurchflussImpuls() const {
    return durchflussImpuls;
}

void Durchflusssensor::setDurchflussImpuls(bool Impuls){
    durchflussImpuls = Impuls;
}

int Durchflusssensor::getImpulsCount() const {
    return impulsCount;
}

void Durchflusssensor::incrementImpuls(){
    impulsCount++;
}
