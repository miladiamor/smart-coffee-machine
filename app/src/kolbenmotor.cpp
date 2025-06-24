#include "kolbenmotor.h"

Kolbenmotor::Kolbenmotor(QObject *parent)
    : QObject{parent},
    status(motorStatus::Aus) {}

void Kolbenmotor::runterfahren() {
    status = motorStatus::runterfahren;
}

void Kolbenmotor::hochfahren() {
    status = motorStatus::hochfahren;
}

void Kolbenmotor::stoppen() {
    status = motorStatus::Aus;
}

Kolbenmotor::motorStatus Kolbenmotor::getStatus() {
    return status;
}
