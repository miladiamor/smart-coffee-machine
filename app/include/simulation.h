#pragma once


#include <QObject>
#include <QTimer>
#include "kolbenmotor.h"
#include "inkrementalencoder.h"
#include "bruehgruppe.h"
#include "Heizelemente.h"
#include "Heizregler.h"
#include "Schaeumer.h"
#include "Temperatursensor.h"
#include "Zuckerdispenser.h"
#include "Tankwaage.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation();
    void setMilch(Tankwaage *milch);
    void setWasser(Tankwaage *wasser);
    void setKaffee(Tankwaage *kaffee);
    void setZucker(Tankwaage *zucker);
    void setKaffeerestbehaelter(Tankwaage *kaffeerestbehaelter);
    void setKolbenmotor(Kolbenmotor *kolbenmotor);
    void setBruehgruppe(Bruehgruppe *bruehgruppe);
    void setInkrementalencoder(Inkrementalencoder *inkrementalencoder);
    bool entnehmeZutat(Tankwaage* tank, int menge, float faktor);
public slots:
    void update(int delta_t_ms);

private:
    //Aktoren
    Kolbenmotor *kolbenmotor;
    Bruehgruppe *bruehgruppe;
    Heizelemente heizelemente;
    Heizregler heizregler;
    Zuckerdispenser zuckerdispenser;
    Schaeumer schaeumer;
    Tankwaage *wasser;
    Tankwaage *milch;
    Tankwaage *kaffee;
    Tankwaage *zucker;
    //Sensoren
    Inkrementalencoder *inkrementalencoder;
    Tankwaage *kaffeerestbehaelter;
    Temperatursensor temperatursensor;

    //physische Werte
    float motorPosition_mm, kaffeerestbehaelter_fuellstand_g, wassertemperatur_cel;
};
