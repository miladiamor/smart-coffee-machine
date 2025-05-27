#include "bruehgruppe.h"
#include <QTimer>

Bruehgruppe::Bruehgruppe() :
    tropfstopfventil(new Ventil), wasserzufuhr(new Ventil), kaffeezufuhr(new Ventil),
    entleerklappe(new Klappe),
    stampfer(new Kolbenmotor),
    inkrementalencoder(new Inkrementalencoder(stampfer)) {}

Bruehgruppe::~Bruehgruppe(){
    delete tropfstopfventil;
    delete wasserzufuhr;
    delete kaffeezufuhr;
    delete entleerklappe;
    delete stampfer;
    delete inkrementalencoder;
}

void Bruehgruppe::kaffee_pressen(int stampfHoehe_mm){
    stampfer->runterfahren();
    while(inkrementalencoder->getPosition() > stampfHoehe_mm) {}
    stampfer->stoppen();
}

void Bruehgruppe::entleeren(){
    entleerklappe->oeffnen();
    stampfer->runterfahren();
    QTimer::singleShot(500, entleerklappe, &Klappe::schliessen);
    stampfer->hochfahren();
}

void Bruehgruppe::wasserzufuhr_oeffnen(){
    wasserzufuhr->oeffnen();
    stampfer->runterfahren();
}

void Bruehgruppe::wasserzufuhr_schliessen(){
    wasserzufuhr->schliessen();
}

void Bruehgruppe::kaffeepulver_hinzufuegen(int menge_g){
    kaffeezufuhr->oeffnen();
    int waitTime = 50*menge_g;
    QTimer::singleShot(waitTime, kaffeezufuhr, &Ventil::schliessen);
}

bool Bruehgruppe::getEntleerklappeOffen(){
    return entleerklappe->get_ist_offen();
}
