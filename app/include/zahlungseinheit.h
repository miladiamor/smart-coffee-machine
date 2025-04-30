#ifndef ZAHLUNGSEINHEIT_H
#define ZAHLUNGSEINHEIT_H

#include "muenzroehrenspeicher.h"
#include "geldscheinbehaelter.h"
#include "ausgabeeinheit.h"
#include "produkt.h"

class Zahlungseinheit
{
public:

    Zahlungseinheit(Muenzroehrenspeicher* roehren, GeldscheinBehaelter* scheine);


    void waehleProdukt(Produkt* p);                      // Produkt auswählen
    bool versucheZahlung(Ausgabeeinheit* ausgabe);       // Zahlung prüfen und ggf. Produkt ausgeben
    void zahlungAbbrechen(Ausgabeeinheit* ausgabe);      // Zahlung abbrechen und Rückgeld ausgeben

private:
    Muenzroehrenspeicher* roehren;       // Zeiger auf den Münzröhrenspeicher
    GeldscheinBehaelter* scheine;       // Zeiger auf den Geldscheinbehälter
    Produkt* produkt;                  // Zeiger auf das aktuell gewählte Produkt
};

#endif // ZAHLUNGSEINHEIT_H
