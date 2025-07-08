#pragma once
#include "Heizelemente.h"
#include "Temperatursensor.h"

#include <QObject>

class Heizregler : public QObject{
    Q_OBJECT

    public:
        Heizregler(QObject *parent = nullptr) : QObject(parent),
            eingeschaltet(false),
            zieltemperatur_Cel(0),
            aktuelleTemperatur_Cel(20),
            sensor (nullptr),
            heizen (nullptr) {}
        ~Heizregler() {}
        bool getEingeschaltet();
        void temperaturRegeln(int zieltemperatur_Cel);
        bool istTemperaturErreicht() const;

        void setHeizelement(Heizelemente *heizelement);
        void setTemperatursensor(Temperatursensor *temperatursensor);
    public slots:
        void tick();

    private:
        bool eingeschaltet;
        int zieltemperatur_Cel;
        int aktuelleTemperatur_Cel;
        Temperatursensor *sensor;
        Heizelemente *heizen;
};

