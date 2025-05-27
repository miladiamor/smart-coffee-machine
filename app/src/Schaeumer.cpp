#include "schaeumer.h"
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
