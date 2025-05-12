#include "Ressourcen.h"

// Getter methods
int Ressourcen::getKaffeemenge_ml() const {
    return kaffeemenge_ml;
}

int Ressourcen::getMilchmenge_ml() const {
    return milchmenge_ml;
}

short Ressourcen::getZuckermenge_TL() const {
    return zuckermenge_TL;
}

int Ressourcen::getWassermenge_ml() const {
    return wassermenge_ml;
}

int Ressourcen::getRestkaffee() const {
    return restkaffee;
}

// Setter methods
void Ressourcen::setKaffeemenge_ml(int menge) {
    kaffeemenge_ml = menge;
}

void Ressourcen::setMilchmenge_ml(int menge) {
    milchmenge_ml = menge;
}

void Ressourcen::setZuckermenge_TL(short tl) {
    zuckermenge_TL = tl;
}

void Ressourcen::setWassermenge_ml(int menge) {
    wassermenge_ml = menge;
}

void Ressourcen::setRestkaffee(int menge) {
    restkaffee = menge;
}
