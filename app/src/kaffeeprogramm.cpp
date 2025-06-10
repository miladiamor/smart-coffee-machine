#include "Kaffeeprogramm.h"
class Bruehgruppe;

Kaffeeprogramm::Kaffeeprogramm()
    : wassermenge_g(0),
    milchmenge_ml(0),
    kaffeemenge_g(0),
    wasserKochhitze_Cel(0),
    milchKochhitze_Cel(0),
    mitZucker(false),
    milchZuerst(false),
    stampfHoehe_mm(0),
    produkt(nullptr)
{}

Kaffeeprogramm::Kaffeeprogramm(Ressourcen benoetigteRessourcen)
    : benoetigteRessourcen(benoetigteRessourcen),
    wassermenge_g(0),
    milchmenge_ml(0),
    kaffeemenge_g(0),
    wasserKochhitze_Cel(0),
    milchKochhitze_Cel(0),
    mitZucker(false),
    milchZuerst(false),
    produkt(nullptr)
{}

// Getters
int Kaffeeprogramm::getKaffeemenge_g() const {
    return kaffeemenge_g;
}

int Kaffeeprogramm::getMilchmenge_ml() const {
    return milchmenge_ml;
}

int Kaffeeprogramm::getWassermenge_ml() const {
    return wassermenge_g;
}

int Kaffeeprogramm::getWasserKochhitze_Cel() const {
    return wasserKochhitze_Cel;
}

int Kaffeeprogramm::getMilchKochhitze_Cel() const {
    return milchKochhitze_Cel;
}

bool Kaffeeprogramm::getMitZucker() const {
    return mitZucker;
}

bool Kaffeeprogramm::getMilchZuerst() const {
    return milchZuerst;
}

bool Kaffeeprogramm::getstampfHoehe_mm() const
{
    return stampfHoehe_mm;
}

Produkt* Kaffeeprogramm::getProdukt() const {
    return produkt;
}

Ressourcen Kaffeeprogramm::getBenoetigteRessourcen() const {
    return benoetigteRessourcen;
}

// Setters
void Kaffeeprogramm::setKaffeemenge_g(int g) {
    kaffeemenge_g = g;
}

void Kaffeeprogramm::setMilchmenge_ml(int ml) {
    milchmenge_ml = ml;
}

void Kaffeeprogramm::setWassermenge_ml(int ml) {
    wassermenge_g = ml;
}

void Kaffeeprogramm::setWasserKochhitze_Cel(int temp) {
    wasserKochhitze_Cel = temp;
}

void Kaffeeprogramm::setMilchKochhitze_Cel(int temp) {
    milchKochhitze_Cel = temp;
}

void Kaffeeprogramm::setMitZucker(bool mit) {
    mitZucker = mit;
}

void Kaffeeprogramm::setMilchZuerst(bool zuerst) {
    milchZuerst = zuerst;
}

void Kaffeeprogramm::setstampfHoehe_mm(bool mm)
{
    stampfHoehe_mm = mm;
}

void Kaffeeprogramm::setProdukt(Produkt* p) {
    produkt = p;
}

void Kaffeeprogramm::setBenoetigteRessourcen(Ressourcen r) {
    benoetigteRessourcen = r;
}
