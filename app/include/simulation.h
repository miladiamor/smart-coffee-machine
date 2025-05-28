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
#include "Durchflusssensor.h"
#include "Pumpe.h"
#include "Schaeumer.h"



class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation();

    void setKaffeerestbehaelter(Tankwaage *kaffeerestbehaelter);
    void setKolbenmotor(Kolbenmotor *kolbenmotor);
    void setBruehgruppe(Bruehgruppe *bruehgruppe);
    void setInkrementalencoder(Inkrementalencoder *inkrementalencoder);
    void setWasserzaehler(Durchflusssensor *sensor);
    void setMilchZaehler(Durchflusssensor *sensor);
    void setWasserPumpe(Pumpe *pumpe);
    void setMilchPumpe (Pumpe *pumpe);
    void setSchaeumer (Schaeumer *schaeumer);


public slots:
    void update(int delta_t_ms);

private:
    //Aktoren
    Kolbenmotor *kolbenmotor;
    Bruehgruppe *bruehgruppe;
    Heizelemente heizelemente;
    Heizregler heizregler;
    Zuckerdispenser zuckerdispenser;
    Schaeumer *schaeumer;
    Pumpe *wasserpumpe;
    Pumpe *milchpumpe;



    //Sensoren
    Inkrementalencoder *inkrementalencoder;
    Tankwaage *kaffeerestbehaelter;
    Temperatursensor temperatursensor;
    Durchflusssensor *wasserzaehler;
    Durchflusssensor *milchzaehler;


    // Temperaturen
    float wassertemperatur_cel, milchtemperatur_cel;
    // Motor
    float motorPosition_mm;
    // Tankfüllstände
    float kaffeerestbehaelter_fuellstand_g;
    // Brühgruppefüllstand
    float bruehkammerInhalt_g;
};
