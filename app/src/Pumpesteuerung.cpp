#include "Pumpesteuerung.h"
#include "Pumpe.h"
#include "Durchflusssensor.h"
#include <QTimer>
#include <QDebug>


Pumpesteuerung::Pumpesteuerung(Pumpe *wasserpumpe, Pumpe *milchpumpe, Durchflusssensor *wasserzaehler, Durchflusssensor *milchzaehler)
    /*: menge_mil(0), wasserpumpe(wasserpumpe), milchpumpe(milchpumpe), wasserzaehler(wasserzaehler), milchzaehler(milchzaehler)*/
    : currentState(Pumpesteuerungstates::IDLE),
    wasserpumpe(wasserpumpe),
    milchpumpe(milchpumpe),
    wasserzaehler(wasserzaehler),
    milchzaehler(milchzaehler),
    targetamount_ml(0)
{}
Pumpesteuerungstates Pumpesteuerung::getState() const{

    return currentState;
}


void Pumpesteuerung::startPumpingWater(int menge_ml) {

    if (currentState != Pumpesteuerungstates::IDLE){
        emit fehler("Pumpe in process");
    return;
    }
    targetamount_ml = menge_ml;
    wasserzaehler->reset();
    wasserpumpe->pumpeStarten();
    setState(Pumpesteuerungstates::PUMPING_WATER);
}

void Pumpesteuerung::startPumpingMilk(int menge_ml) {

    if (currentState != Pumpesteuerungstates::IDLE){
        emit fehler("Pumpe in process");
        return;
    }
    targetamount_ml = menge_ml;
    milchzaehler->reset();
    milchpumpe->pumpeStarten();
    setState(Pumpesteuerungstates::PUMPING_MILK);
}

void Pumpesteuerung::tick(){
    switch (currentState) {
    case Pumpesteuerungstates::PUMPING_WATER:
        if((wasserzaehler->getDurchflussImpuls() >= targetamount_ml)) {
                wasserpumpe->pumpeStoppen();
                setState(Pumpesteuerungstates::PUMPING_COMPLETE);
                emit pumpingFinished();
                setState(Pumpesteuerungstates::IDLE);
                }
        break;

    case Pumpesteuerungstates::PUMPING_MILK:
        if((milchzaehler->getDurchflussImpuls() >= targetamount_ml)) {
                milchpumpe->pumpeStoppen();
                setState(Pumpesteuerungstates::PUMPING_COMPLETE);
                emit pumpingFinished();
                setState(Pumpesteuerungstates::IDLE);
                }
        break;
    case Pumpesteuerungstates::IDLE:
    case Pumpesteuerungstates::PUMPING_COMPLETE:
    case Pumpesteuerungstates::ERROR:
        break;
    }
}

void Pumpesteuerung::setState(Pumpesteuerungstates newState)
{
    if(currentState == newState) return;
    currentState = newState;
}

//void Pumpesteuerung::pumpen(float wassermenge){

//    menge_mil = wassermenge;
//    wasserpumpe->pumpeStarten();
//QTimer::singleShot(500, wasserpumpe, &Pumpe::pumpeStoppen);
//wasserpumpe->pumpeStoppen();
//}
/*
void Pumpesteuerung::mypumpe1(int wassermenge)
{
    menge_mil = wassermenge;
    wasserpumpe->pumpeStarten();
}

void Pumpesteuerung::mypumpe2(int milchmenge)
{
    menge_mil = milchmenge;
    milchpumpe->pumpeStarten();
}*/
