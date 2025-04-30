#ifndef RESSOURCEN_H
#define RESSOURCEN_H

class Ressourcen
{
private:
    int kaffeemenge_ml;
    int milchmenge_ml;
    int wassermenge_ml;
    int zuckermenge_g;

public:
    // Constructor
    Ressourcen();

    // Getters
    int getKaffeemenge_ml() const;
    int getMilchmenge_ml() const;
    int getWassermenge_ml() const;
    int getZuckermenge_g() const;

    // Setters
    void setKaffeemenge_ml(int menge);
    void setMilchmenge_ml(int menge);
    void setWassermenge_ml(int menge);
    void setZuckermenge_g(int menge);
};

#endif // RESSOURCEN_H
