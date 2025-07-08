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
    Fuellstandsmessung();
    Fuellstandsmessung(Tankwaage* wasser,
                       Tankwaage* milch,
                       Tankwaage* kaffee,
                       Tankwaage* zucker,
                       Ressourcen* ressourcen);

    bool updateRessourcen();
    Ressourcen* getRessourcen() const;

    bool hatGenug(Tankwaage* tank, int mengeEinheit, float faktor = 1.0f) const;

    void setWasserTank(Tankwaage *Tank);
    void setMilchTank(Tankwaage *Tank);
    void setKaffeeTank(Tankwaage *Tank);
    void setRessourcen(Ressourcen *Tank);

    Tankwaage* getWasserTank() const { return wasser; }
    Tankwaage* getMilchTank() const { return milch; }
    Tankwaage* getKaffeeTank() const { return kaffee; }
    Tankwaage* getZuckerTank() const { return zucker; }
};
