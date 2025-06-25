#include "Zuckerdispenser.h"
#include <QTimer>

Zuckerdispenser::Zuckerdispenser(QObject *parent)
    : QObject{parent} {}


void Zuckerdispenser::zuckerAuswerfen(){
    if(eingeschaltet){
        return;
    }
    eingeschaltet = true;
}

void Zuckerdispenser::ausschalten(){
    eingeschaltet = false;
}

bool Zuckerdispenser::istAktiv() const{
    return eingeschaltet;
}

