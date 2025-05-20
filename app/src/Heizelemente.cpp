#include "Heizelemente.h"
#include <QDebug>

Heizelemente::Heizelemente() {
    temperatur_Cel = 20;
    zieltemperatur_Cel = 0;
}

void Heizelemente::einschalten() {
    qDebug() << "Heizelement eingeschaltet.";
}

void Heizelemente::ausschalten() {
    qDebug() << "Heizelement ausgeschaltet.";
}
