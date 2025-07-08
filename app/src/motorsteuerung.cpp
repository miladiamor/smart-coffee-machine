#include "motorsteuerung.h"
#include <cmath>
#include <QDebug>
/*
Motorsteuerung::Motorsteuerung(QObject *parent)
    : QObject{parent}
{}
*/

void Motorsteuerung::stampferAusfahren(float stampfhoehe_mm){
    this->stampfhoehe_mm = stampfhoehe_mm;
    position_mm = inkrementalencoder->getPosition_mm();
    if (stampfhoehe_mm == position_mm) {bruehgruppe->trigger(MOTORABGESCHLOSSEN); return;}
    eingeschaltet = true;
    if (position_mm < stampfhoehe_mm) {
        stampfer->hochfahren();
    } else {
        stampfer->runterfahren();
    }
}

void Motorsteuerung::tick() {
    //qDebug() << "Eingeschaltet in motorsteuerung: " << eingeschaltet;
    if (eingeschaltet) {
        position_mm = inkrementalencoder->getPosition_mm();
        //qDebug() << "stampfhoehe in motorsteuerung: " << stampfhoehe_mm;
        //qDebug() << "position in motorsteuerung: " << position_mm;
        if (std::abs(stampfhoehe_mm - position_mm) <= 0.2) {
            stampfer->stoppen();
            eingeschaltet = false;
            bruehgruppe->trigger(MOTORABGESCHLOSSEN);
        }
    }
}

void Motorsteuerung::setBruehgruppe(Bruehgruppe *bruehgruppe){
    this->bruehgruppe = bruehgruppe;
}

void Motorsteuerung::setInkrementalencoder(Inkrementalencoder *inkrementalencoder){
    this->inkrementalencoder = inkrementalencoder;
}

void Motorsteuerung::setStampfer(Kolbenmotor *stampfer){
    this->stampfer = stampfer;
}
