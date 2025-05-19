#pragma once
#include "Behaelter.h"
#include "Ressourcen.h"
#include "Rezept.h"

class Fuellstandsmessung {
private:
    Behaelter* wasser;
    Behaelter* milch;
    Behaelter* kaffee;
    Behaelter* zucker;
    Behaelter* restkaffee;

    Ressourcen* ressourcen;

public:
    Fuellstandsmessung(Behaelter* wasser,
                       Behaelter* milch,
                       Behaelter* kaffee,
                       Behaelter* zucker,
                       Behaelter* restkaffee,
                       Ressourcen* ressourcen);

    void updateRessourcen();
    bool hatGenugZutaten(const Rezept& rezept);
    void verbraucheZutaten(const Rezept& rezept);
};
