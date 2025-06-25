#pragma once

#include "Produkt.h"
#include "Ressourcen.h"

class Kaffeeprogramm {
public:
    Kaffeeprogramm() = default;
    Kaffeeprogramm(Ressourcen benoetigteRessourcen);

    // Getters
    int getKaffeemenge_g() const;
    int getMilchmenge_ml() const;
    int getWassermenge_ml() const;
    int getWasserKochhitze_Cel() const;
    int getMilchKochhitze_Cel() const;
    bool getMitZucker() const;
    bool getMilchZuerst() const;
    float getstampfHoehe_mm() const;
    Produkt* getProdukt() const;
    Ressourcen getBenoetigteRessourcen() const;

    // Setters
    void setKaffeemenge_g(int kaffeemenge_g);
    void setMilchmenge_ml(int milchmenge_ml);
    void setWassermenge_ml(int wassermenge_ml);
    void setWasserKochhitze_Cel(int wasserKochhitze_Cel);
    void setMilchKochhitze_Cel(int milchKochhitze_Cel);
    void setMitZucker(bool mitZucker);
    void setMilchZuerst(bool milchZuerst);
    void setstampfHoehe_mm(float mm);
    void setProdukt(Produkt* produkt);
    void setBenoetigteRessourcen(Ressourcen r);

private:
    Ressourcen benoetigteRessourcen;
    int wassermenge_g;
    int milchmenge_ml;
    int kaffeemenge_g;
    int wasserKochhitze_Cel;
    int milchKochhitze_Cel;
    bool mitZucker;
    bool milchZuerst;
    bool stampfHoehe_mm;
    Produkt* produkt;
};
