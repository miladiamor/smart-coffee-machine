#pragma once

#include "Produkt.h"
class Kaffeeprogramm {
public:
    Kaffeeprogramm();

    int getKaffeemenge_g() const;
    int getMilchmenge_ml() const;
    int getWassermenge_ml() const;
    bool getMitZucker() const;
    Produkt* getProdukt() const;

    void setKaffeemenge_g(int g);
    void setMilchmenge_ml(int ml);
    void setWassermenge_ml(int ml);
    void setMitZucker(bool mit);
    void setProdukt(Produkt* produkt);

private:
    int kaffeemenge_g, milchmenge_ml, wassermenge_g;
    bool mitZucker;
    Produkt* produkt;
};
