#ifndef KAFFEEPROGRAMM_H
#define KAFFEEPROGRAMM_H

class Kaffeeprogramm
{
public:
    Kaffeeprogramm();
    int getKaffeemenge_g();
    int getMilchmenge_ml();
    int getWassermenge_ml();
    bool getMitZucker();

    void setKaffeemenge_g();
    void setMilchmenge_ml();
    void setWassermenge_ml();
    void setMitZucker();
private:
    int kaffeemenge_g, milchmenge_ml, wassermenge_g;

    bool mitZucker;
};

#endif // KAFFEEPROGRAMM_H
