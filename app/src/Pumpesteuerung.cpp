#include "Pumpesteuerung.h"
#include "Pumpe.h"
#include "Durchflusssensor.h"
#include <QTimer>
#include <QDebug>
Pumpesteuerung::Pumpesteuerung(Pumpe *wasserpumpe, Pumpe *milchpumpe, Durchflusssensor *wasserzaehler, Durchflusssensor *milchzaehler)
    : menge_mil(0), wasserpumpe(wasserpumpe), milchpumpe(milchpumpe), wasserzaehler(wasserzaehler), milchzaehler(milchzaehler){

    pumpen = new QTimer(this);
    connect(pumpen, SIGNAL(timeout()),this,SLOT(mypumpe()));
    pumpen->start(5000);
}

//void Pumpesteuerung::pumpen(float wassermenge){

//    menge_mil = wassermenge;
//    wasserpumpe->pumpeStarten();
    //QTimer::singleShot(500, wasserpumpe, &Pumpe::pumpeStoppen);
    //wasserpumpe->pumpeStoppen();
//}

void Pumpesteuerung::mypumpe1(float wassermenge)
{
    menge_mil = wassermenge;
    wasserpumpe->pumpeStarten();
}

void Pumpesteuerung::mypumpe2(float milchmenge)
{
    menge_mil = milchmenge;
    milchpumpe->pumpeStarten();
}

