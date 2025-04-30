#ifndef AUSGABEEINHEIT_H
#define AUSGABEEINHEIT_H

#include "produkt.h"

class Ausgabeeinheit
{
public:

    Ausgabeeinheit();

    void wechselgeldAusgeben(float betrag);     // Gibt Wechselgeld aus
    void rueckgeldZurueckgeben(float betrag);      // Gibt Geld bei Abbruch zurück
    void produktAusgeben(Produkt* produkt);      // Gibt das gewählte Produkt aus
};

#endif // AUSGABEEINHEIT_H
