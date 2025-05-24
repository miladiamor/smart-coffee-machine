#pragma once
#include <string>

struct Rezept {
    std::string name;
    int wasser_g;
    int milch_ml;
    int kaffee_g;
    int zucker_TL;

    // Constructor for quick creation
    Rezept(const std::string& name, int wasser, int milch, int kaffee, int zucker)
        : name(name),
        wasser_g(wasser),
        milch_ml(milch),
        kaffee_g(kaffee),
        zucker_TL(zucker) {}
};
