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
    void setMilchheizer(Heizelemente *milchHeizer);
    void setWasserheizer(Heizelemente *wasserHeizer);
    void setKolbenmotor(Kolbenmotor *kolbenmotor);
    void setInkrementalencoder(Inkrementalencoder *inkrementalencoder);
    void setWasserPumpe(Pumpe *pumpe);
    void setMilchPumpe (Pumpe *pumpe);
    void setSchaeumer (Schaeumer *schaeumer);
    void setMuenzEingabeSensor(MuenzEingabeSensor *muenzeingabesensor);
    void setWasserTemperatursensor(Temperatursensor *sensor);
    void setMilchTemperatursensor(Temperatursensor *sensor);
    void setMuenze_EUR(float muenze_EUR);
    void setTropfstopfVentil(Ventil *v);
    void setWasserVentil(Ventil *v);
    void setKaffeeVentil(Ventil *v);
    void setZuckerdispenser(Zuckerdispenser *zuckerdispenser);
    //void setMainWindow(MainWindow *mw);

signals:
    void setKaffeeInhalt(float kaffee);

public slots:
    void tick();

private:
    // MainWindow (um Kaffee abzudaten)
    //MainWindow *mw;

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
    Temperatursensor *milchTemperatursensor, *wasserTemperatursensor;

    //Sensoren Füllstandmessung
    Tankwaage *kaffeerestbehaelter,
        *wasserbehaelter, *kaffeebehaelter,
        *milchbehaelter,
        *zuckerbehaelter;

    // Sensor Münze
    MuenzEingabeSensor *muenzSensor;

    //Münze
    float muenze_EUR = 0.0;

    // Temperaturen
    float wasserrohrtemperatur_cel = 25, milchrohrtemperatur_cel = 25;
    // Tasseinhalt
    float kaffeeTassenInhalt_g = 0;
    float milchSchaum_g = 0;

    // Motor
    float motorPosition_mm = MAX_MOTOR_HEIGHT_MM;
    // Tankfüllstände
    float kaffeerestbehaelter_g, kaffeebehaelter_g, wasserbehaelter_g, milchbehaelter_g, zuckerbehaelter_g;
    // Brühgruppefüllstand
    float bruehkammerKaffeeinhalt_g = 0;
};
