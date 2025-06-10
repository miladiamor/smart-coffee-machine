#include "bruehgruppe.h"
#include "kolbenmotor.h"
#include <QTimer>

Bruehgruppe::Bruehgruppe() :
    tickCount(0),
    currentState(WARTEN), nextState(WARTEN),
    tropfstopfventil(new Ventil), wasserzufuhr(new Ventil), kaffeezufuhr(new Ventil),
    entleerklappe(new Klappe),
    stampfer(new Kolbenmotor),
    inkrementalencoder(new Inkrementalencoder(stampfer)) {}

Bruehgruppe::~Bruehgruppe(){
    /*delete tropfstopfventil;
    delete wasserzufuhr;
    delete kaffeezufuhr;
    delete entleerklappe;
    delete stampfer;
    delete inkrementalencoder;
    */
}

void Bruehgruppe::tick() {
    const int tickmenge = 10*kaffeeprogramm->getKaffeemenge_g();
    switch (currentState) {
    case WARTEN:
        break;
    case KAFFEEZUFUHR:
        tickCount++;
        if (tickCount == tickmenge) {
            trigger(STAMPFEN);
            tickCount = 0;
        }
        break;
    case STAMPFEN:
        if (stampfer->getStatus() == Kolbenmotor::motorStatus::runterfahren && inkrementalencoder->getPosition_mm() == kaffeeprogramm->getstampfHoehe_mm()) {
            trigger(KOCHBEREIT);
        }
        break;
    case KOCHBEREIT:
        break;
    case ENTLEEREN:
        if (inkrementalencoder->getPosition_mm() == 0) {
            trigger(ZURUECKSETZEN);
        }
    case ZURUECKSETZEN:
        if (inkrementalencoder->getPosition_mm() == 25) {
            trigger(WARTEN);
        }
        break;
    tickCount++;
    }
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
        /*
        if (nextState == WARTEN && !kaffeezufuhr->get_ist_offen()) {
            currentState = WARTEN;
        }
        */
        break;
    case STAMPFEN:
        if (stampfer->getStatus() == Kolbenmotor::motorStatus::runterfahren && inkrementalencoder->getPosition_mm() == kaffeeprogramm->getstampfHoehe_mm()) {
            stampfer->stoppen();
            wasserzufuhr->oeffnen();
            tropfstopfventil->oeffnen();
            currentState = KOCHBEREIT;
        }
        /*
        if (nextState == KOCHEN && wasserzufuhr->get_ist_offen() && tropfstopfventil->get_ist_offen()) {
            currentState = KOCHEN;
        }
*/
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

state Bruehgruppe::getState() {
    return currentState;
}

void Bruehgruppe::entleeren() {
    trigger(ENTLEEREN);
}

void Bruehgruppe::kaffeeFuellen() {
    trigger(KAFFEEZUFUHR);
}
