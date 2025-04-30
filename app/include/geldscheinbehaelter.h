#ifndef GELDSCHEINBEHAELTER_H
#define GELDSCHEINBEHAELTER_H

#include "geldschein.h"

class GeldscheinBehaelter
{
public:
    // Konstruktor
    GeldscheinBehaelter();

    // Methoden
    bool istVoll() const;                 // Prüft, ob der Behälter voll ist
    bool fuegeHinzu(Geldschein* s);         // Fügt einen Geldschein hinzu
    float gesamtWert() const;              // Gesamtwert der enthaltenen Scheine
    void leeren();                         // Entfernt alle Scheine

private:
    int anzahlScheine;                     // Aktuelle Anzahl der Scheine im Behälter
    const int maxKapazitaet = 10;            // Maximale Anzahl der erlaubten Scheine
};

#endif // GELDSCHEINBEHAELTER_H
