#pragma once

#include "Behaelter.h"
#include "Ressourcen.h"

class Fuellstandsmessung {
private:
    Ressourcen* ressourcen;
    Behaelter* wasser;
    Behaelter* zucker;
    Behaelter* milch;
    Behaelter* kaffee;
    Behaelter* restkaffee;

public:
    Fuellstandsmessung(Ressourcen* ress,
                       Behaelter* wasser,
                       Behaelter* zucker,
                       Behaelter* milch,
                       Behaelter* kaffee,
                       Behaelter* restkaffee);

    void mengenPruefen();
    Ressourcen getMengen() const;
};
