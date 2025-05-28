#include "Zuckerdispenser.h"
#include <QDebug>
#include <QTimer>
#include <QThread>

Zuckerdispenser::Zuckerdispenser(){
    eingeschaltet = false;
}

void Zuckerdispenser::zuckerAuswerfen(){
    eingeschaltet = true;
    //QTimer::singleShot(500, eingeschaltet, &Zuckerdispenser::ausschalten);
    QThread::msleep(5000);
    eingeschaltet = false;
}
bool Zuckerdispenser::istAktiv() const{
    return eingeschaltet;
}

