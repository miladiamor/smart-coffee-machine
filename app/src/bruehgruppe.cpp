#include "bruehgruppe.h"
#include "kolbenmotor.h"
#include <QTimer>

Bruehgruppe::(QObject *parent)
    : QObject{parent}

Bruehgruppe::~Bruehgruppe(){
    /*delete tropfstopfventil;
    delete wasserzufuhr;
    delete kaffeezufuhr;
    delete entleerklappe;
    delete stampfer;
    delete inkrementalencoder;
    */
}

void Bruehgruppe::trigger(state nextState) {
    switch(currentState){
    case WARTEN:
        if (nextState == KAFFEEZUFUHR) {
            kaffeezufuhr->oeffnen();
            tickCount = 0;
            currentState = KAFFEEZUFUHR;
        }
        break;
    case KAFFEEZUFUHR:
        if (nextState == STAMPFEN) {
            kaffeezufuhr->schliessen();
            currentState = STAMPFEN;
            stampfer->runterfahren();
        }
        break;
    case STAMPFEN:
        if (stampfer->getStatus() == Kolbenmotor::motorStatus::runterfahren && inkrementalencoder->getPosition_mm() == kaffeeprogramm->getstampfHoehe_mm()) {
            stampfer->stoppen();
            wasserzufuhr->oeffnen();
            tropfstopfventil->oeffnen();
            currentState = KOCHBEREIT;
        }
        break;
    case KOCHBEREIT:
        if (nextState == ENTLEEREN) {
            wasserzufuhr->schliessen();
            tropfstopfventil->schliessen();
            entleerklappe->oeffnen();
            stampfer->runterfahren();
            currentState = ENTLEEREN;
        }
        break;
    case ENTLEEREN:
        if (nextState == ZURUECKSETZEN) {
            stampfer->hochfahren();
            entleerklappe->schliessen();
            currentState = ZURUECKSETZEN;
        }
        break;
    case ZURUECKSETZEN:
        if (nextState == WARTEN) {
            stampfer->stoppen();
            currentState = WARTEN;
        }
    }
}

BruehState Bruehgruppe::getState() {
    return state;
}
