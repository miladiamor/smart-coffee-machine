#include "bruehgruppe.h"
#include "kolbenmotor.h"
#include <QTimer>

Bruehgruppe::Bruehgruppe(QObject *parent)
    : QObject{parent} {}

Bruehgruppe::~Bruehgruppe(){
    /*delete tropfstopfventil;
    delete wasserzufuhr;
    delete kaffeezufuhr;
    delete entleerklappe;
    delete stampfer;
    delete inkrementalencoder;
    */
}

void Bruehgruppe::trigger(BruehEvent event) {
    switch(state){
    case WARTEN:
        if (event == ZUFUHRSTART) {
            kaffeezufuhr->oeffnen();
            state = KAFFEEZUFUHR;
        }
        break;
    case KAFFEEZUFUHR:
        if (event == ZUFUHRABGESCHLOSSEN) {
            kaffeezufuhr->schliessen();
            motorsteuerung->stampferAusfahren(kaffeeprogramm->getstampfHoehe_mm());
            state = STAMPFEN;
        }
        break;
    case STAMPFEN:
        if (event == MOTORABGESCHLOSSEN) {
            wasserzufuhr->oeffnen();
            tropfstopfventil->oeffnen();
            state = KOCHEN;
        }
        break;
    case KOCHEN:
        if (event == KOCHENAUFGEHOERT) {
            wasserzufuhr->schliessen();
            tropfstopfventil->schliessen();
            entleerklappe->oeffnen();
            motorsteuerung->stampferAusfahren(0);
            state = ENTLEEREN;
        }
        break;
    case ENTLEEREN:
        if (event == MOTORABGESCHLOSSEN) {
            motorsteuerung->stampferAusfahren(MAX_MOTOR_HEIGHT_MM);
            entleerklappe->schliessen();
            state = ZURUECKSETZEN;
        }
        break;
    case ZURUECKSETZEN:
        if (event == MOTORABGESCHLOSSEN) {
            state = WARTEN;
        }
    }
}

void Bruehgruppe::setEntleerklappe(Klappe *entleerklappe){
    this->entleerklappe = entleerklappe;
}

void Bruehgruppe::setKaffeeprogramm(Kaffeeprogramm *kaffeeprogramm){
    this->kaffeeprogramm = kaffeeprogramm;
}

void Bruehgruppe::setMotorsteuerung(Motorsteuerung *motorsteuerung){
    this->motorsteuerung = motorsteuerung;
}

void Bruehgruppe::setTropfstopfventil(Ventil *tropfstopfventil){
    this->tropfstopfventil = tropfstopfventil;
}

void Bruehgruppe::setWasserzufuhr(Ventil *wasserzufuhr){
    this->wasserzufuhr = wasserzufuhr;
}

void Bruehgruppe::setKaffeezufuhr(Ventil *kaffeeezufuhr){
    this->kaffeezufuhr = kaffeeezufuhr;
}

BruehState Bruehgruppe::getState() {
    return state;
}
