#ifndef GELDSCHEINSENSOR_H
#define GELDSCHEINSENSOR_H

#include "geldscheinbehaelter.h"

class GeldscheinSensor
{
public:
    // Konstruktor
    GeldscheinSensor(GeldscheinBehaelter* behaelter);

    // Methoden
    void erkenneSchein(float betrag);

private:
    GeldscheinBehaelter* behaelter;   // Zeiger auf den GeldscheinBehälter
};

#endif // GELDSCHEINSENSOR_H
