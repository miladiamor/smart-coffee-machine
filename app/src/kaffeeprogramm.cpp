#include "Kaffeeprogramm.h"

Kaffeeprogramm::Kaffeeprogramm()
    : kaffeemenge_g(0),
    milchmenge_ml(0),
    wassermenge_g(0),
    mitZucker(false),
    produkt(nullptr)
{}

int Kaffeeprogramm::getKaffeemenge_g() const {
    return kaffeemenge_g;
}

int Kaffeeprogramm::getMilchmenge_ml() const {
    return milchmenge_ml;
}

int Kaffeeprogramm::getWassermenge_ml() const {
    return wassermenge_g;
}

bool Kaffeeprogramm::getMitZucker() const {
    return mitZucker;
}

Produkt* Kaffeeprogramm::getProdukt() const {
    return produkt;
}

void Kaffeeprogramm::setKaffeemenge_g(int g) {
    kaffeemenge_g = g;
}

void Kaffeeprogramm::setMilchmenge_ml(int ml) {
    milchmenge_ml = ml;
}

void Kaffeeprogramm::setWassermenge_ml(int ml) {
    wassermenge_g = ml;
}

void Kaffeeprogramm::setMitZucker(bool mit) {
    mitZucker = mit;
}

void Kaffeeprogramm::setProdukt(Produkt* produkt) {
    this->produkt = produkt;
}
