#ifndef MUENZAUSWERFER_H
#define MUENZAUSWERFER_H

#include "muenzroehre.h"

class MuenzAuswerfer {
private:
    Muenzroehre *aktiveRoehre;
public:
    MuenzAuswerfer(); // Standardkonstruktor für Unittest

    // Wirft eine einzelne Münze aus bei ungueltiger Eingabe
    void auswerfenMuenze(Muenzroehre *aktiveRoehre);
};

#endif
