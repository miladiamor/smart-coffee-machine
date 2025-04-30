#ifndef MUENZSENSOR_H
#define MUENZSENSOR_H

#include "muenzroehrenspeicher.h"

class MuenzSensor
{
public:
    // Konstruktor
    MuenzSensor(Muenzroehrenspeicher* speicher);

    // Methoden
    void erkenneMuenze(float eingeworfen);

private:
    Muenzroehrenspeicher* speicher;   // Zeiger auf den Münzröhrenspeicher
};

#endif // MUENZSENSOR_H
