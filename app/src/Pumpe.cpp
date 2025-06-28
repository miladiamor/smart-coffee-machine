#include "Pumpe.h"


Pumpe::Pumpe() {

    starten = false;
}

Pumpe::~Pumpe(){}

void Pumpe::pumpeStarten(){
    starten = true;
}

void Pumpe::pumpeStoppen(){
    starten = false;
}

bool Pumpe::istAktiv() const {
    return starten;
}
