#include "Ressourcen.h"

Ressourcen::Ressourcen()
    : kaffeemenge_g(0), milchmenge_ml(0), wassermenge_ml(0),
    zuckermenge_TL(0), restkaffee_g(0) {}

int Ressourcen::getKaffeemenge_g() const {
    return kaffeemenge_g;
}

int Ressourcen::getMilchmenge_ml() const {
    return milchmenge_ml;
}

int Ressourcen::getWassermenge_ml() const {
    return wassermenge_ml;
}

short Ressourcen::getZuckermenge_TL() const {
    return zuckermenge_TL;
}

int Ressourcen::getRestkaffee_g() const {
    return restkaffee_g;
}

void Ressourcen::setKaffeemenge_g(int menge) {
    kaffeemenge_g = menge;
}

void Ressourcen::setMilchmenge_ml(int menge) {
    milchmenge_ml = menge;
}

void Ressourcen::setWassermenge_ml(int menge) {
    wassermenge_ml = menge;
}

void Ressourcen::setZuckermenge_TL(short tl) {
    zuckermenge_TL = tl;
}

void Ressourcen::setRestkaffee_g(int menge) {
    restkaffee_g = menge;
}
