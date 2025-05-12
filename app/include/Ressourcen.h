#pragma once

class Ressourcen {
private:
    int kaffeemenge_ml;
    int milchmenge_ml;
    short zuckermenge_TL;
    int wassermenge_ml;
    int restkaffee;

public:
    // Getter methods
    int getKaffeemenge_ml() const;
    int getMilchmenge_ml() const;
    short getZuckermenge_TL() const;
    int getWassermenge_ml() const;
    int getRestkaffee() const;

    // Setter methods
    void setKaffeemenge_ml(int menge);
    void setMilchmenge_ml(int menge);
    void setZuckermenge_TL(short tl);
    void setWassermenge_ml(int menge);
    void setRestkaffee(int menge); // ← add this
};



