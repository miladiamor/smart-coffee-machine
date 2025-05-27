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
