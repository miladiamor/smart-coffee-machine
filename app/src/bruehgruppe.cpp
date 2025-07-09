#include "bruehgruppe.h"
#include "motorsteuerung.h"
#include "qdebug.h"
#include <QTimer>

/*
Bruehgruppe::~Bruehgruppe(){
    delete tropfstopfventil;
    delete wasserzufuhr;
    delete kaffeezufuhr;
    delete entleerklappe;
    delete stampfer;
    delete inkrementalencoder;

}
*/

Kaffeeprogramm *Bruehgruppe::getKaffeeprogramm() {
    return this->kaffeeprogramm;
}

void Bruehgruppe::trigger(BruehEvent event) {
    switch(state){
    case WARTEN:
        if (event == ZUFUHRSTART) {
            kaffeezufuhr->oeffnen();
            state = KAFFEEZUFUHR;
            qDebug() << "BG: KAFFEEZUFUHR";
        }
        break;
    case KAFFEEZUFUHR:
        if (event == ZUFUHRABGESCHLOSSEN) {
            kaffeezufuhr->schliessen();
            motorsteuerung->stampferAusfahren(kaffeeprogramm->getStampfhoehe_mm());
            state = STAMPFEN;

            qDebug() << "BG: STAMPFEN";
        }
        break;
    case STAMPFEN:
        if (event == MOTORABGESCHLOSSEN) {
            wasserzufuhr->oeffnen();
            tropfstopfventil->oeffnen();
            state = KOCHEN;
            qDebug() << "BG: KOCHEN";
        }
        break;
    case KOCHEN:
        if (event == KOCHENAUFGEHOERT) {
            wasserzufuhr->schliessen();
            tropfstopfventil->schliessen();
            entleerklappe->oeffnen();
            motorsteuerung->stampferAusfahren(0);
            state = ENTLEEREN;
            qDebug() << "BG: KOCHENAUFGEHOERT";
        }
        break;
    case ENTLEEREN:
        if (event == MOTORABGESCHLOSSEN) {
            motorsteuerung->stampferAusfahren(20);
            entleerklappe->schliessen();
            state = ZURUECKSETZEN;
            qDebug() << "BG: ZURUECKSETZEN";
        }
        break;
    case ZURUECKSETZEN:
        if (event == MOTORABGESCHLOSSEN) {
            qDebug() << "BG: WARTEN";
            state = WARTEN;
        }
        break;
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

void Bruehgruppe::setState(BruehState state) {
    this->state = state;
}
