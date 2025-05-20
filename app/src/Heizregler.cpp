#include "Heizregler.h"
#include <QDebug>

Heizregler::Heizregler() {
    zieltemperatur_Cel = 0;
    heizen = new Heizelemente();
    sensor = new Temperatursensor();
}

void Heizregler::temperaturRegeln(int Zieltemperatur_Cel) {
    zieltemperatur_Cel = Zieltemperatur_Cel;
    int aktuelleTemperatur = sensor->getTemperatur_Cel();

    qDebug() << "Zieltemperatur:" << zieltemperatur_Cel;
    qDebug() << "Aktuelle Temperatur:" << aktuelleTemperatur;

    if (aktuelleTemperatur < zieltemperatur_Cel) {
        einschalten();
    } else {
        ausschalten();
    }
}

void Heizregler::regelnStoppen() {
    ausschalten();
    qDebug() << "Regelung gestoppt.";
}

void Heizregler::einschalten() {
    qDebug() << "Heizregler schaltet Heizung ein.";

}

void Heizregler::ausschalten() {
    qDebug() << "Heizregler schaltet Heizung aus.";

}
