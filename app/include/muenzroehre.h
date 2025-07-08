#pragma once


class Muenzroehre {
private:

    int aktuelleAnzahl;

public:

    Muenzroehre(int kapazitaet, float wert);

    // Standardkonstruktor fuer Unittest
    Muenzroehre();

    bool istVoll() const;
    int getAnzahl() const;
    void erhoeheAnzahl();
    void reduziereAnzahl();
};
