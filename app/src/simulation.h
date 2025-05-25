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

class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation(Kolbenmotor *kolbenmotor, Bruehgruppe *bruehgruppe, Inkrementalencoder *inkrementalencoder);

public slots:
    void update(int delta_t_ms);
    void starteHeizung();
    void setzeZucker(int level);
    void starteSchaeumer();

private:
    //Aktoren
    Kolbenmotor *kolbenmotor;
    Bruehgruppe *bruehgruppe;

    //Sensoren
    Inkrementalencoder *inkrementalencoder;
    float motorPosition_mm, kaffeerestbehaelter_fuellstand_g;

    //Components
    Heizelemente heizelemente;
    Heizregler heizregler;
    Temperatursensor temperatursensor;
    Zuckerdispenser zuckerdispenser;
    Schaeumer schaeumer;
};
