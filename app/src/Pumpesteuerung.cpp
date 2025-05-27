#include "Pumpesteuerung.h"
#include "Pumpe.h"
#include "Durchflusssensor.h"
#include <QTimer>

Pumpesteuerung::Pumpesteuerung(Pumpe *wasserpumpe, Pumpe *milchpumpe, Durchflusssensor *wasserzaehler, Durchflusssensor *milchzaehler)
    : menge_mil(0), wasserpumpe(wasserpumpe), milchpumpe(milchpumpe), wasserzaehler(wasserzaehler), milchzaehler(milchzaehler){}

void Pumpesteuerung::pumpen(float wassermenge){

    menge_mil = wassermenge;
    wasserpumpe->pumpeStarten();
    QTimer::singleShot(500, wasserpumpe, &Pumpe::pumpeStoppen);
    wasserpumpe->pumpeStoppen();
}
