#include "bruehgruppe.h"
#include <QTimer>

Bruehgruppe::Bruehgruppe() :
    tropfstopfventil(new Ventil), wasserzufuhr(new Ventil), kaffeezufuhr(new Ventil),
    entleerklappe(new Klappe),
    stampfer(new Kolbenmotor),
    inkrementalencoder(new Inkrementalencoder(stampfer)) {}

void Bruehgruppe::kaffee_pressen(int stampfHoehe_mm){
    stampfer->runterfahren();
    while(inkrementalencoder->get_position_in_mm() > stampfHoehe_mm) {}
    stampfer->stoppen();
}

void Bruehgruppe::entleeren(){
}

void Bruehgruppe::tropfstopfventil_schliessen(){

}

void Bruehgruppe::tropfstopfventil_oeffnen(){

}

void Bruehgruppe::wasserzufuhr_oeffnen(){

}

void Bruehgruppe::wasserzufuhr_schliessen(){

}

void Bruehgruppe::kaffeepulver_hinzufuegen(int menge_g){
    kaffeezufuhr->oeffnen();
    int waitTime = 50*menge_g;
    QTimer::singleShot(waitTime, kaffeezufuhr, &Ventil::schliessen);
}

int get_status(){

}
