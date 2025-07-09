#include "Fuellstandsmessung.h"
#include <QDebug>

Fuellstandsmessung::Fuellstandsmessung() {
    wasser = nullptr;
    milch = nullptr;
    kaffee = nullptr;
    zucker = nullptr;
    ressourcen = nullptr;
}
Fuellstandsmessung::Fuellstandsmessung(Tankwaage* wasser,
                                       Tankwaage* milch,
                                       Tankwaage* kaffee,
                                       Tankwaage* zucker,
                                       Ressourcen* ressourcen)
    : wasser(wasser), milch(milch), kaffee(kaffee), zucker(zucker), ressourcen(ressourcen) {}

bool Fuellstandsmessung::updateRessourcen() {
    if (!wasser || !milch || !kaffee || !zucker || !ressourcen)
        return false;

    ressourcen->setWassermenge_ml((int)wasser->gewichtPruefen());
    ressourcen->setMilchmenge_ml((int)milch->gewichtPruefen());
    ressourcen->setKaffeemenge_g(static_cast<int>(kaffee->gewichtPruefen()));
    ressourcen->setZuckermenge_TL(static_cast<short>(zucker->gewichtPruefen()));

    return true;
}

Ressourcen* Fuellstandsmessung::getRessourcen() const {
    return ressourcen;
}

bool Fuellstandsmessung::hatGenug(Tankwaage* tank, int mengeEinheit, float faktor) const {
    if (!tank) return false;
    qDebug() << "in hatGenug";
    float benoetigt_g = mengeEinheit * faktor;
    qDebug() << "gewicht: " << (float)tank->gewichtPruefen();
    return tank->gewichtPruefen() >= benoetigt_g;
}

void Fuellstandsmessung::setWasserTank(Tankwaage *Tank) {wasser = Tank;}

void Fuellstandsmessung::setMilchTank(Tankwaage *Tank) {milch = Tank;}

void Fuellstandsmessung::setKaffeeTank(Tankwaage *Tank) {kaffee = Tank;}

void Fuellstandsmessung::setRessourcen(Ressourcen *Tank) {ressourcen = Tank;}

void Fuellstandsmessung::setZuckerTank(Tankwaage *Tank)
{
    this->zucker = Tank;
}
