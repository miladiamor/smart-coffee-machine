#include "Fuellstandsmessung.h"

Fuellstandsmessung::Fuellstandsmessung(std::shared_ptr<Tankwaage> wasser,
                                       std::shared_ptr<Tankwaage> milch,
                                       std::shared_ptr<Tankwaage> kaffee,
                                       std::shared_ptr<Tankwaage> zucker,
                                       std::shared_ptr<Tankwaage> restkaffee,
                                       std::shared_ptr<Ressourcen> ressourcen)
    : wasser(wasser), milch(milch), kaffee(kaffee), zucker(zucker),
    restkaffee(restkaffee), ressourcen(ressourcen) {}

bool Fuellstandsmessung::updateRessourcen() {
    if (!wasser || !milch || !kaffee || !zucker || !restkaffee || !ressourcen)
        return false;

    constexpr double MILCH_DICHTE = 1.03;
    constexpr int ZUCKER_GRAMM_PRO_TL = 5;

    ressourcen->setWassermenge_ml(wasser->gewichtPruefen());
    ressourcen->setMilchmenge_ml(static_cast<int>(milch->gewichtPruefen() / MILCH_DICHTE));
    ressourcen->setKaffeemenge_g(kaffee->gewichtPruefen());
    ressourcen->setZuckermenge_TL(static_cast<short>(zucker->gewichtPruefen() / ZUCKER_GRAMM_PRO_TL));
    ressourcen->setRestkaffee_g(restkaffee->gewichtPruefen());

    return true;
}

bool Fuellstandsmessung::hatGenugZutaten(const Rezept& rezept) {
    if (!wasser || !milch || !kaffee || !zucker) return false;

    return wasser->hatGenug(rezept.wasser_g) &&
           milch->hatGenug(rezept.milch_ml) &&
           kaffee->hatGenug(rezept.kaffee_g) &&
           zucker->hatGenug(rezept.zucker_TL * 5);
}

void Fuellstandsmessung::verbraucheZutaten(const Rezept& rezept) {
    if (!wasser || !milch || !kaffee || !zucker) return;

    wasser->entnehmen(rezept.wasser_g);
    milch->entnehmen(rezept.milch_ml);
    kaffee->entnehmen(rezept.kaffee_g);
    zucker->entnehmen(rezept.zucker_TL * 5);
}

std::shared_ptr<Ressourcen> Fuellstandsmessung::getRessourcen() const {
    return ressourcen;
}
