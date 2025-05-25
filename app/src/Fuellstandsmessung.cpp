#include "Fuellstandsmessung.h"

Fuellstandsmessung::Fuellstandsmessung(Tankwaage* wasser,
                                       Tankwaage* milch,
                                       Tankwaage* kaffee,
                                       Tankwaage* zucker,
                                       Ressourcen* ressourcen)
    : wasser(wasser), milch(milch), kaffee(kaffee), zucker(zucker), ressourcen(ressourcen) {}

bool Fuellstandsmessung::updateRessourcen() {
    if (!wasser || !milch || !kaffee || !zucker || !ressourcen)
        return false;

    constexpr double MILCH_DICHTE = 1.03;
    constexpr int ZUCKER_GRAMM_PRO_TL = 5;

    ressourcen->setWassermenge_ml(wasser->gewichtPruefen());
    ressourcen->setMilchmenge_ml(static_cast<int>(milch->gewichtPruefen() / MILCH_DICHTE));
    ressourcen->setKaffeemenge_g(kaffee->gewichtPruefen());
    ressourcen->setZuckermenge_TL(static_cast<short>(zucker->gewichtPruefen() / ZUCKER_GRAMM_PRO_TL));


    return true;
}

Ressourcen* Fuellstandsmessung::getRessourcen() const {
    return ressourcen;
}
