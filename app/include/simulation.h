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
#include "Pumpe.h"
#include "Schaeumer.h"
#include "QThread"



class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation();

    void setKaffeerestbehaelter(Tankwaage *kaffeerestbehaelter);
    void setKolbenmotor(Kolbenmotor *kolbenmotor);
    void setBruehgruppe(Bruehgruppe *bruehgruppe);
    void setInkrementalencoder(Inkrementalencoder *inkrementalencoder);
    void setWasserPumpe(Pumpe *pumpe);
    void setMilchPumpe (Pumpe *pumpe);
    void setSchaeumer (Schaeumer *schaeumer);


public slots:
    void tick();

private:
    //Aktoren Brühgruppe
    Kolbenmotor *kolbenmotor;
    Ventil *tropfstopfVentil, *kaffeezufuhrVentil;
    Klappe *entleerklappe;

    //Sensoren Brühgruppe
    Inkrementalencoder *inkrementalencoder;

    // Aktoren Programmsteuerung
    Zuckerdispenser *zuckerdispenser;
    Schaeumer *schaeumer;
    Pumpe *wasserpumpe;
    Pumpe *milchpumpe;

    // Sensoren Programmsteuerung
    Heizelemente *heizelemente;
    Temperatursensor temperatursensor;

    //Sensoren Füllstandmessung
    Tankwaage *kaffeerestbehaelter,
        *wasserbehaelter, *kaffeebehaelter,
        *milchbehaelter,
        *zuckerbehaelter;

    // Temperaturen
    float wassertemperatur_cel, milchtemperatur_cel;
    // Motor
    float motorPosition_mm;
    // Tankfüllstände
    float kaffeerestbehaelter_fuellstand_g, kaffeebehaelter_g;
    // Brühgruppefüllstand
    float bruehkammerInhalt_g, kaffeehoehe_mm;
};
