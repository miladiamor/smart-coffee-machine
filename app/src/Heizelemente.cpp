#include "Heizelemente.h"
#include <QDebug>

//Heizelemente::Heizelemente() : eingeschaltet(false){}

void Heizelemente::einschalten() {
    eingeschaltet = true;
}

void Heizelemente::ausschalten() {
    eingeschaltet = false;

}

bool Heizelemente::istEingeschaltet() const{
    return eingeschaltet;
}
