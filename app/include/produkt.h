#ifndef PRODUKT_H
#define PRODUKT_H

#include <string>

class Produkt
{
public:
    // Konstruktor
    Produkt(std::string name, float preis);

    // Getter-Methoden
    std::string getName() const;
    float getPreis() const;

private:
    // Attribute
    std::string name;
    float preis;
};

#endif // PRODUKT_H
