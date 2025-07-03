#ifndef PRODUKT_H
#define PRODUKT_H

#include <string>

class Produkt {
private:
    std::string name;
    float preis;
    int anzahl;

public:
    Produkt(std::string name, float preis, int anzahl);

    std::string getName() const;
    float getPreis() const;
    int getAnzahl() const;
    void dekrementiereAnzahl();
};

#endif
