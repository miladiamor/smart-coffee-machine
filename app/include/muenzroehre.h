#ifndef MUENZROEHRE_H
#define MUENZROEHRE_H

class Muenzroehre {
private:
    int kapazitaet;
    int aktuelleAnzahl;

public:
    Muenzroehre(int kapazitaet);
    ~Muenzroehre();

    bool istVoll() const;
    void leeren();

    int getAktuelleAnzahl() const;
    int getKapazitaet() const;
    void erhoeheAnzahl();
    void reduziereAnzahl();
};

#endif
