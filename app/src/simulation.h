#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>
#include "kolbenmotor.h"
#include "inkrementalencoder.h"
#include "bruehgruppe.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation(Kolbenmotor *kolbenmotor, Bruehgruppe *bruehgruppe, Inkrementalencoder *inkrementalencoder);

public slots:
    void update(int delta_t_ms);

private:
    //Aktoren
    Kolbenmotor *kolbenmotor;
    Bruehgruppe *bruehgruppe;

    //Sensoren
    Inkrementalencoder *inkrementalencoder;
    float motorPosition_mm, kaffeerestbehaelter_fuellstand_g;
};

#endif // SIMULATION_H
