#pragma once
#include "Tankwaage.h"
#include "Ressourcen.h"


class Fuellstandsmessung {
private:
    Tankwaage* wasser;
    Tankwaage* milch;
    Tankwaage* kaffee;
    Tankwaage* zucker;
    Tankwaage* restkaffee;

    Ressourcen* ressourcen;

public:
    Fuellstandsmessung(Tankwaage* wasser,
                       Tankwaage* milch,
                       Tankwaage* kaffee,
                       Tankwaage* zucker,
                       Tankwaage* restkaffee,
                       Ressourcen* ressourcen);

    bool updateRessourcen();
    Ressourcen* getRessourcen() const;
};
