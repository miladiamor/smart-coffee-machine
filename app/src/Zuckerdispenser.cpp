#include "Zuckerdispenser.h"
#include <QDebug>
#include <QTimer>

Zuckerdispenser::Zuckerdispenser(){
    eingeschaltet = false;
}

void Zuckerdispenser::zuckerAuswerfen(){
    eingeschaltet = true;
    QTimer::singleShot(500, eingeschaltet, &Zuckerdispenser::ausschalten);
    //eingeschaltet = false;
}
bool Zuckerdispenser::istAktiv() const{
    return eingeschaltet;
}

