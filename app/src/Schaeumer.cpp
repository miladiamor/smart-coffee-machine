#include "schaeumer.h"

Schaeumer::Schaeumer() : eingeschaltet(false) {
}

bool Schaeumer::getEingeschaltet(){
    return eingeschaltet;
}

void Schaeumer::aufschaeumenStarten() {
    this->eingeschaltet = true;

}

void Schaeumer::aufschaeumenStoppen() {
    this->eingeschaltet = false;
}


