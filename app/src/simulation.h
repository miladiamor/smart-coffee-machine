#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <QTimer>
#include "kolbenmotor.h"
#include "inkrementalencoder.h"

class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation(Kolbenmotor *kolbenmotor);

signals:
    void inkrementalencoderUpdate(int position_mm);

public slots:
    void update();

private:
    Kolbenmotor *kolbenmotor;
    int motorPosition_mm;
};

#endif // SIMULATION_H
