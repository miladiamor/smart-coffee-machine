#include "Zuckerdispenser.h"
#include <QTimer>


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

