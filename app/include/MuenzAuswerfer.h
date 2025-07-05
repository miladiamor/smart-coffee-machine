#ifndef MUENZAUSWERFER_H
#define MUENZAUSWERFER_H

#include <iostream>

class MuenzAuswerfer {
public:
    MuenzAuswerfer(); // Standardkonstruktor für Unit-Tests

    // Wirft den angegebenen Geldbetrag aus (als Rückgeld bei Abbruch oder Zahlung)
    void auswerfen(float betrag);

    // Wirft eine einzelne Münze aus (bei ungültiger Eingabe)
    void auswerfenMuenze(float wert);
};

#endif
