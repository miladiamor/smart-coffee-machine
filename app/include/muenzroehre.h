#ifndef MUENZROEHRE_H
#define MUENZROEHRE_H

class Muenzroehre {
private:
    float wert;
    int kapazitaet;
    int aktuelleAnzahl;

public:
    Muenzroehre(float wert, int kapazitaet);
    Muenzroehre(int kapazitaet);

    bool istVoll() const;
    void leeren();

    int getAktuelleAnzahl() const;
    int getKapazitaet() const;
    float getWert() const;

    void erhoeheAnzahl();
};

#endif
