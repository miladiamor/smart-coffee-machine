#include "schaeumer.h"
#include "Pumpesteuerung.h"
#include <QDebug>

Schaeumer::Schaeumer() : eingeschaltet(false) {
}

bool Schaeumer::getEingeschaltet(){
    return eingeschaltet;
}

void Schaeumer::aufschaeumenStarten() {
    this->eingeschaltet = true;
    qDebug() << "Milchschaumvorgang gestartet.";
}

void Schaeumer::aufschaeumenStoppen() {
    this->eingeschaltet = false;
    qDebug() << "Milchschaumvorgang gestoppt.";
}


/*
void Pumpesteuerung::mypumpe(float wassermenge)
{
    menge_mil = wassermenge;
    wasserpumpe->pumpeStarten();
}
*/
