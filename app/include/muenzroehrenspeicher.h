#ifndef MUENZROEHRENSPEICHER_H
#define MUENZROEHRENSPEICHER_H

#include "muenzroehre.h"

class Muenzroehrenspeicher
{
public:
    // Konstruktor
    Muenzroehrenspeicher();

    // Methoden
    bool fuegeMuenzeEin(float wert);   // Münze in passende Röhre einfügen
    float gesamtWert() const;         // Gesamtwert aller Münzröhren
    void leeren();                    // Alle Röhren leeren

private:
    Muenzroehre* roehre2Euro;            // Röhre für 2 Euro Münzen
    Muenzroehre* roehre1Euro;            // Röhre für 1 Euro Münzen
    Muenzroehre* roehre50Cent;           // Röhre für 50 Cent Münzen
    Muenzroehre* roehre20Cent;           // Röhre für 20 Cent Münzen
    Muenzroehre* roehre10Cent;           // Röhre für 10 Cent Münzen
};

#endif // MUENZROEHRENSPEICHER_H
