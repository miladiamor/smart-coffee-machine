#include "Pumpe.h"

void Pumpe::pumpeStarten(){
    ist_Aktiv = true;
}

void Pumpe::pumpeStoppen(){
    ist_Aktiv = false;
}

bool Pumpe::get_Aktiv() {
    return ist_Aktiv;
}
