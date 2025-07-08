#include "Zuckerdispenser.h"

//Zuckerdispenser::Zuckerdispenser(QObject *parent)
//    : QObject(parent), eingeschaltet(false){}

//Zuckerdispenser::~Zuckerdispenser(){}

void Zuckerdispenser::zuckerAuswerfen() {
    if (eingeschaltet) {
        return;
    }
    eingeschaltet = true;
    //emit auswerfenGestartet();

    eingeschaltet = false;
    //emit auswerfenBeendet();
}

void Zuckerdispenser::ausschalten() {
    eingeschaltet = false;
}

bool Zuckerdispenser::istAktiv() const {
    return eingeschaltet;
}

void Zuckerdispenser::setZuckerdispenser(Zuckerdispenser *zucker)
{

}
