#include "kolbenmotor.h"

Kolbenmotor::Kolbenmotor() : status(0) {

}

void Kolbenmotor::runterfahren() {
    status = 1;
}

void Kolbenmotor::hochfahren() {
    status = 2;
}

void Kolbenmotor::stoppen() {
    status = 0;
}

int Kolbenmotor::getStatus() {
    return status;
}
