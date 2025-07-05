#ifndef MUENZAUSWERFER_H
#define MUENZAUSWERFER_H

#include <iostream>

class MuenzAuswerfer {
public:
    // Wirft den angegebenen Geldbetrag aus ( als Rueckgeld bei Abbruch oder Zahlung)
    void auswerfen(float betrag);

    // Wirft eine einzelne Muenze aus ( bei ungueltiger Eingabe)
    void auswerfenMuenze(float wert);
};

#endif




