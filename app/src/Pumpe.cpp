#include "Pumpe.h"

Pumpe::Pumpe() {

    this->starten = false;
}

void Pumpe::pumpeStarten(){
    this->starten = true;
}

void Pumpe::pumpeStoppen(){
    this->starten = false;
}

bool Pumpe::istAktiv() const {
    return status != 0;
}
