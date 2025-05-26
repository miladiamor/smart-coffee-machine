#include "Heizregler.h"
#include <QDebug>

Heizregler::Heizregler() {
    heizen = new Heizelemente();
    sensor = new Temperatursensor();
}

bool Heizregler::getEingeschaltet(){
    return this->eingeschaltet;
}

void Heizregler::temperaturRegeln(int zieltemperatur_Cel) {
    this->zieltemperatur_Cel = zieltemperatur_Cel;
    heizen->einschalten();
    while((eingeschaltet == true) && (sensor->getTemperatur_Cel() < zieltemperatur_Cel)) {}
    heizen->ausschalten();
    //qDebug() << "Zieltemperatur:" << zieltemperatur_Cel;
    //qDebug() << "Aktuelle Temperatur:" << aktuelleTemperatur;
}
/*
void Heizregler::regelnStoppen() {
    this->eingeschaltet = false;
    qDebug() << "Regelung gestoppt.";
}
*/
/*
void Heizregler::einschalten() {
    qDebug() << "Heizregler schaltet Heizung ein.";

}

void Heizregler::ausschalten() {
    qDebug() << "Heizregler schaltet Heizung aus.";

}
*/
