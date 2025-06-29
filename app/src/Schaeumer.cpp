#include "Schaeumer.h"

//Schaeumer::Schaeumer() : eingeschaltet(false) {}

//Schaeumer::~Schaeumer(){}

bool Schaeumer::getEingeschaltet(){
    return eingeschaltet;
}

void Schaeumer::aufschaeumenStarten() {
    eingeschaltet = true;
}

void Schaeumer::aufschaeumenStoppen() {
    eingeschaltet = false;
}


