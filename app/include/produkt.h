#pragma once
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

