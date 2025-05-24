#pragma once
#include <memory>
#include "Tankwaage.h"
#include "Ressourcen.h"
#include "Rezept.h"

class Fuellstandsmessung {
private:
    std::shared_ptr<Tankwaage> wasser;
    std::shared_ptr<Tankwaage> milch;
    std::shared_ptr<Tankwaage> kaffee;
    std::shared_ptr<Tankwaage> zucker;
    std::shared_ptr<Tankwaage> restkaffee;

    std::shared_ptr<Ressourcen> ressourcen;

public:
    Fuellstandsmessung(std::shared_ptr<Tankwaage> wasser,
                       std::shared_ptr<Tankwaage> milch,
                       std::shared_ptr<Tankwaage> kaffee,
                       std::shared_ptr<Tankwaage> zucker,
                       std::shared_ptr<Tankwaage> restkaffee,
                       std::shared_ptr<Ressourcen> ressourcen);

<<<<<<< HEAD
    bool updateRessourcen();
    bool hatGenugZutaten(const Rezept& rezept);
    void verbraucheZutaten(const Rezept& rezept);

    std::shared_ptr<Ressourcen> getRessourcen() const;
=======
    void updateRessourcen();
    bool hatGenugZutaten(const Rezept& rezept);
    void verbraucheZutaten(const Rezept& rezept);
>>>>>>> 8ea25da2c898e00a70edbd5e09d231440374e7b1
};
