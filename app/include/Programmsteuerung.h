#pragma once
#ifndef PROGRAMMSTEUERUNG_H
#define PROGRAMMSTEUERUNG_H

#include <QObject>
#include <QTimer>


class Schaeumer;
class Zuckerdispenser;
class Bruehgruppe;
class Heizregler;
class Pumpesteuerung;
class Fuellstandsmessung;
class Kaffeeprogramm;
class Clock;

class Programmsteuerung : public QObject {
    Q_OBJECT

private:
    enum class CoffeeState{
        IDLE,
        HEIZEN,
        FUELLEN,
        PUMPING_WATER,
        PUMPING_MILK,
        SCHAEUMEN,
        PROGRAMM_ABGESCHLOSSEN,
        FEHLER
    };
private:
    int status;
    int tickCounter;
    Kaffeeprogramm *programm;
    Kaffeeprogramm* currentProgramm;

    Heizregler *temperaturregler_wasser, *temperaturregler_milch;
    Zuckerdispenser* zucker;
    Schaeumer* milchschaeumer;
    Bruehgruppe* bruehgruppe;
    Pumpesteuerung* steuerung;
    Fuellstandsmessung* messung;
    CoffeeState coffeeState;

public:
    Programmsteuerung();
    ~Programmsteuerung();
    void setPumpesteuerung(Pumpesteuerung* pump_steuerung);
    void setMilchschaeumer(Schaeumer *milchschaeumer);
    void setWasserHeizer(Heizregler* heizer);
    void setMilchHeizer(Heizregler* heizer);
    void setBruehgruppe(Bruehgruppe* gruppee);
    void ausfuehren(Kaffeeprogramm *programm);
    void tick();

private slots:
    void onPumpingFinished();
    void nextStep();
    void fehleraufgetreten(const QString& message);
};

#endif
