#include "Zuckerdispenser.h"
#include <QDebug>
#include <QTimer>

Zuckerdispenser::Zuckerdispenser(){
    eingeschaltet = false;
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, this, &Zuckerdispenser::ausschalten);
}

void Zuckerdispenser::zuckerAuswerfen(){
    eingeschaltet = true;
    timer.start
}
bool Zuckerdispenser::istAktiv() const{
    return eingeschaltet;
}
