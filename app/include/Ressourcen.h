#pragma once

class Ressourcen {
private:
    int kaffeemenge_g;
    int milchmenge_ml;
    int wassermenge_ml;
    short zuckermenge_TL;
    int restkaffee_g;

public:
    Ressourcen();

    int getKaffeemenge_g() const;
    int getMilchmenge_ml() const;
    int getWassermenge_ml() const;
    short getZuckermenge_TL() const;
    int getRestkaffee_g() const;

    void setKaffeemenge_g(int menge);
    void setMilchmenge_ml(int menge);
    void setWassermenge_ml(int menge);
    void setZuckermenge_TL(short tl);
    void setRestkaffee_g(int menge);
};
