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

// Temperatur und Regler
#define HEIZRATE_WASSER_CEL_PRO_TICK 0.5f  // während der Heizung Temperatur erhöht sich
#define PUMPEN_PRO_TICK 10;
// Wasser wird in der Kaffee gemwandelt
#define MILCH_MAXTEMP_CEL             65.0f
#define MILCH_STARTTEMP_CEL           25.0f
#define MILCH_HEIZRATE_CEL_PRO_TICK   0.5f
#define MILCH_KUEHLRATE_CEL_PRO_TICK  0.5f

// Motorgeschwindigkeit definieren
#define MOTOR_MAX_HEIGHT_MM 25
#define MOTORGESCHWINDIGKEIT_MM_PRO_TICK 0.1
// Kaffeezufuhur
#define KAFFEEZUFUHR_G_PRO_TICK 0.1
// Entleern
#define BEHAELTER_MAX_FUELLSTAND_G 10000
// max tasse
#define KAFFEETASSENINHALT_G_MAX 450

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

    void setKaffeeTassenInhalt_g(float kaffeeTassenInhalt_g);

signals:
    void setKaffeeInhalt(int kaffee);

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
