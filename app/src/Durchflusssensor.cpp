#include "Durchflusssensor.h"

Durchflusssensor::Durchflusssensor() :durchflussImpuls(false), impulsCount(0) {}

bool Durchflusssensor::getDurchflussImpuls() const {
    return durchflussImpuls;
}

void Durchflusssensor::setDurchflussImpuls(bool Impuls){
    durchflussImpuls = Impuls;
}

float Durchflusssensor::getWassermenge_g() const {
    return wassermenge_g;
}

void Durchflusssensor::addWassermenge_g(float menge_g) {
    wassermenge_g += menge_g;
}

void Durchflusssensor::setNull() {
    wassermenge_g = 0.0;
}
