#include "Tankwaage.h"

Tankwaage::Tankwaage(float gewicht_g) : gewicht_g(gewicht_g) {}

float Tankwaage::gewichtPruefen() const {
    return gewicht_g;
}

void Tankwaage::setGewicht(float gewicht_g) {
    this->gewicht_g = gewicht_g;
}


