#include "Fuellstandsmessung.h"
#include "Ressourcen.h"
Fuellstandsmessung::Fuellstandsmessung(Ressourcen* ress,
                                       Behaelter* wasser,
                                       Behaelter* zucker,
                                       Behaelter* milch,
                                       Behaelter* kaffee,
                                       Behaelter* restkaffee)
    : ressourcen(ress),
    wasser(wasser),
    zucker(zucker),
    milch(milch),
    kaffee(kaffee),
    restkaffee(restkaffee) {}

void Fuellstandsmessung::mengenPruefen() {
    ressourcen->setWassermenge_ml(wasser->gewichtPruefen());
    ressourcen->setZuckermenge_TL(zucker->gewichtPruefen());
    ressourcen->setMilchmenge_ml(milch->gewichtPruefen());
    ressourcen->setKaffeemenge_ml(kaffee->gewichtPruefen());
     ressourcen->setRestkaffee(restkaffee->gewichtPruefen());
}

Ressourcen Fuellstandsmessung::getMengen() const {
    return *ressourcen;
}
