#pragma once
#include "Heizelemente.h"
#include "Temperatursensor.h"

#include <QObject>

class Heizregler : public QObject {

public:
    Heizregler(QObject* parent = nullptr);
    ~Heizregler();

    bool getEingeschaltet();
    void temperaturRegeln(int zieltemperatur_Cel);
    bool istTemperaturErreicht() const;
    void updateTemperatur();

public slots:
    void tick();

private:
    bool eingeschaltet;
    int zieltemperatur_Cel;
    int aktuelleTemperatur_Cel;
    Temperatursensor *sensor;
    Heizelemente *heizen;   
};

