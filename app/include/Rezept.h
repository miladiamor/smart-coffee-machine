#pragma once
#include <string>

struct Rezept {
    std::string name;     // Optional: name like "Espresso"
    int wasser_g;         // Water in grams (same as ml)
    int milch_ml;         // Milk in milliliters ✅
    int kaffee_g;         // Coffee in grams
    int zucker_TL;        // Sugar in teaspoons

    // Constructor for quick creation
    Rezept(const std::string& name, int wasser, int milch, int kaffee, int zucker)
        : name(name),
        wasser_g(wasser),
        milch_ml(milch),
        kaffee_g(kaffee),
        zucker_TL(zucker) {}
};
