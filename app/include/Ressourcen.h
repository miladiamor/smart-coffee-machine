#pragma once

class Ressourcen {
private:
    int wassermenge_ml = 0;
    int milchmenge_ml = 0;
    int kaffeemenge_g = 0;
    short zuckermenge_TL = 0;
    int restkaffee_g = 0;

public:
    void setWassermenge_ml(int ml);
    void setMilchmenge_ml(int ml);
    void setKaffeemenge_g(int g);
    void setZuckermenge_TL(short tl);
    void setRestkaffee_g(int g);


    int getWassermenge_ml() const;
    int getMilchmenge_ml() const;
    int getKaffeemenge_g() const;
    short getZuckermenge_TL() const;
    int getRestkaffee_g() const;

    void reset();
};
