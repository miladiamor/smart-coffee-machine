#include "motorsteuerung.h"

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
    if (eingeschaltet) {
        position_mm = inkrementalencoder->getPosition_mm();
        if ((position_mm >= stampfhoehe_mm - 0.25) && (position_mm <= stampfhoehe_mm + 0.25)) {
            stampfer->stoppen();
            bruehgruppe->trigger(MOTORABGESCHLOSSEN);
            eingeschaltet = false;
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
