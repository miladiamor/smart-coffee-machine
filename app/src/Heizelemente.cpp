#include "Heizelemente.h"
#include <QDebug>

Heizelemente::Heizelemente() : eingeschaltet(false){}

void Heizelemente::einschalten() {
    this->eingeschaltet = true;
}

void Heizelemente::ausschalten() {
    this->eingeschaltet = false;

}

bool Heizelemente::istEingeschaltet() const{
    return this->eingeschaltet;
}
