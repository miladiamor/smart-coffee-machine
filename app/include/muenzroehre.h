#ifndef MUENZROEHRE_H
#define MUENZROEHRE_H

#include "muenze.h" // Für die Münzen

class Muenzroehre
{
public:

    Muenzroehre(float wert, int kapazitaet);


    bool istVoll() const;                  // Prüfen, ob die Röhre voll ist
    bool fuegeHinzu(Muenze* m);               // Eine Münze hinzufügen
    float gesamtWert() const;               // Gesamtwert aller Münzen
    void leeren();                          // Alle Münzen entfernen

private:
    float wert;            // Münzwert dieser Röhre (z.B 0.50 )
    int kapazitaet;         // Maximale Anzahl an Münzen
    int aktuelleAnzahl;    // Derzeitige Münzanzahl
};

#endif // MUENZROEHRE_H
