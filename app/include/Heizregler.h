#pragma once
#include "Heizelemente.h"
#include "Temperatursensor.h"

#include <QObject>

class Heizregler : public QObject {

public:
    Heizregler(QObject* parent = nullptr);
    virtual ~Heizregler();

    virtual bool getEingeschaltet();
    virtual void temperaturRegeln(int zieltemperatur_Cel);
    virtual bool istTemperaturErreicht() const;
    virtual void updateTemperatur();

public slots:
    virtual void tick();

private:
    bool eingeschaltet;
    int zieltemperatur_Cel;
    int aktuelleTemperatur_Cel;
    Temperatursensor *sensor;
    Heizelemente *heizen;   
};

