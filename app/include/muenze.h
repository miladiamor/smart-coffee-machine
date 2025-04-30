#ifndef MUENZE_H
#define MUENZE_H

class Muenze
{
public:
    // Konstruktor: Initialisiert die Münze mit ihrem Nennwert.
    Muenze(float wert);

    // Getter-Methode: Gibt den Nennwert der Münze zurück.
    float getWert() const;

private:
    float wert; // Der Nennwert der Münze
};

#endif // MUENZE_H
