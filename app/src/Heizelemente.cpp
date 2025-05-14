#include "Heizelemente.h"
#include <QDebug>

Heizelemente::Heizelemente(){
    temperatur_Cel = 20; // Anfang's Temp
    zieltemperatur_Cel = 0;
}

void Heizelemente::einschalten(){
    qDebug() <<"Heizung eingeshaltet";
    temperatur_Cel += 1; // simulliert Heizung
}

void Heizelemente::ausschalten(){
    qDebug() <<"Heizung ausgeschaltet";
}
