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
#include "MuenzEingabeSensor.h"


class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation();

    void setKaffeebehaelter(Tankwaage *kaffeebehaelter);
    void setWasserbehaelter(Tankwaage *wasserbehaelter);
    void setMilchbehaelter(Tankwaage *milchbehaelter);
    void setZuckerbehaelter(Tankwaage *zuckerBehaelter);
    void setKaffeerestbehaelter(Tankwaage *kaffeerestbehaelter);
    void setKolbenmotor(Kolbenmotor *kolbenmotor);
    void setInkrementalencoder(Inkrementalencoder *inkrementalencoder);
    void setWasserPumpe(Pumpe *pumpe);
    void setMilchPumpe (Pumpe *pumpe);
    void setSchaeumer (Schaeumer *schaeumer);
    void setMuenzEingabeSensor(MuenzEingabeSensor *muenzeingabesensor);

    void setMuenze_EUR(float muenze_EUR);

public slots:
    void tick();

private:
    //Aktoren Brühgruppe
    Kolbenmotor *kolbenmotor;
    Ventil *tropfstopfVentil, *kaffeezufuhrVentil, *wasserzufuhrVentil;
    Klappe *entleerklappe;

    //Sensoren Brühgruppe
    Inkrementalencoder *inkrementalencoder;

    // Aktoren Programmsteuerung
    Heizelemente *wasserHeizer, *milchHeizer;
    Zuckerdispenser *zuckerdispenser;
    Schaeumer *schaeumer;
    Pumpe *wasserpumpe;
    Pumpe *milchpumpe;

    // Sensoren Programmsteuerung
    Temperatursensor temperatursensor;

    //Sensoren Füllstandmessung
    Tankwaage *kaffeerestbehaelter,
        *wasserbehaelter, *kaffeebehaelter,
        *milchbehaelter,
        *zuckerbehaelter;

    // Sensor Münze
    MuenzEingabeSensor *muenzSensor;

    //Münze
    float muenze_EUR;

    // Temperaturen
    float wasserrohrtemperatur_cel, milchrohrtemperatur_cel;
    // Tasseinhalt
    float kaffeeTassenInhalt_g;
    float milchSchaum_g;

    // Motor
    float motorPosition_mm;
    // Tankfüllstände
    float kaffeerestbehaelter_g, kaffeebehaelter_g, wasserbehaelter_g, milchbehaelter_g, zuckerbehaelter_g;
    // Brühgruppefüllstand
    float bruehkammerKaffeeinhalt_g;
};
