#include "Heizelemente.h"
#include <QDebug>

Heizelemente::Heizelemente() {
    this->eingeschaltet = false;
}

void Heizelemente::einschalten() {
    this->eingeschaltet = true;
    qDebug() << "Heizelement eingeschaltet.";
}

void Heizelemente::ausschalten() {
    this->eingeschaltet = false;
    qDebug() << "Heizelement ausgeschaltet.";
}
