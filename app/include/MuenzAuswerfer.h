#ifndef MUENZAUSWERFER_H
#define MUENZAUSWERFER_H

#include "muenzroehre.h"

class MuenzAuswerfer {
private:
    Muenzroehre *aktiveRoehre;
public:
    MuenzAuswerfer(); // Standardkonstruktor für Unit-Tests

    // Wirft eine einzelne Münze aus (bei ungültiger Eingabe)
    void auswerfenMuenze(float aktiveRoehre);
};

#endif
