#pragma once
#include "produkt.h"

class Ausgabeeinheit
{
public:

    Ausgabeeinheit();

    void wechselgeldAusgeben(float betrag);     // Gibt Wechselgeld aus
    void rueckgeldZurueckgeben(float betrag);      // Gibt Geld bei Abbruch zurueck
    void produktAusgeben(Produkt* produkt);      // Gibt das gehlte Produkt aus
};


