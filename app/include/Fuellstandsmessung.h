#pragma once

#include "Tankwaage.h"
#include "Ressourcen.h"

class Fuellstandsmessung {
private:
    Tankwaage* wasser;
    Tankwaage* milch;
    Tankwaage* kaffee;
    Tankwaage* zucker;

    Ressourcen* ressourcen;

public:
    Fuellstandsmessung(Tankwaage* wasser,
                       Tankwaage* milch,
                       Tankwaage* kaffee,
                       Tankwaage* zucker,
                       Ressourcen* ressourcen);

    bool updateRessourcen();
    Ressourcen* getRessourcen() const;

    bool hatGenug(Tankwaage* tank, int mengeEinheit, float faktor = 1.0f) const;
};
