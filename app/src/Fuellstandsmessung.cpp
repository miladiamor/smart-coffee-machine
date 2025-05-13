#include "Fuellstandsmessung.h"
#include "Rezept.h"
Fuellstandsmessung::Fuellstandsmessung(Behaelter* wasser,
                                       Behaelter* milch,
                                       Behaelter* kaffee,
                                       Behaelter* zucker,
                                       Behaelter* restkaffee,
                                       Ressourcen* ressourcen)
    : wasser(wasser),
    milch(milch),
    kaffee(kaffee),
    zucker(zucker),
    restkaffee(restkaffee),
    ressourcen(ressourcen) {}

void Fuellstandsmessung::updateRessourcen() {
    // Update the Ressourcen object based on current Behaelter status
    ressourcen->setWassermenge_ml(wasser->gewichtPruefen()); // 1g = 1ml
    ressourcen->setMilchmenge_ml(static_cast<int>(milch->gewichtPruefen() / 1.03));
    ressourcen->setKaffeemenge_g(kaffee->gewichtPruefen());
    ressourcen->setZuckermenge_TL(static_cast<short>(zucker->gewichtPruefen() / 5)); // e.g., 5g = 1 TL
    ressourcen->setRestkaffee_g(restkaffee->gewichtPruefen());
}

bool Fuellstandsmessung::hatGenugZutaten(const Rezept& rezept) {
    return wasser->hatGenug(rezept.wasser_g) &&
           milch->hatGenug(rezept.milch_ml) &&
           kaffee->hatGenug(rezept.kaffee_g) &&
           zucker->hatGenug(rezept.zucker_TL * 5); // Convert TL to g (assume 1 TL = 5g)
}

void Fuellstandsmessung::verbraucheZutaten(const Rezept& rezept) {
    wasser->entnehmen(rezept.wasser_g);
    milch->entnehmen(rezept.milch_ml);
    kaffee->entnehmen(rezept.kaffee_g);
    zucker->entnehmen(rezept.zucker_TL * 5);
}
