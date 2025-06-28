#pragma once
#ifndef PROGRAMMSTEUERUNG_H
#define PROGRAMMSTEUERUNG_H

#include <QObject>
#include <QTimer>


class Schaeumer;
class Zuckerdispenser;
class Bruehgruppe;
class Heizregler;
class Fuellstandsmessung;
class Kaffeeprogramm;
class Clock;
class Pumpe;



class Programmsteuerung : public QObject {
    Q_OBJECT

public:
    enum class CoffeeState{
        IDLE,
        HEIZEN,
        WARTENAUFBRUEHGRUPPE,
        KAFFEE_ZUFUHR,
        PUMPING_WATER,
        PUMPING_MILK,
        SCHAEUMEN,
        PROGRAMM_ABGESCHLOSSEN,
        ZUCKERAUSWERFEN,
        ZURUECK_SETZEN,
    };

private:
    bool busy = false;
    int tickCounter;
    Kaffeeprogramm* currentProgramm;

    Heizregler *temperaturregler_wasser, *temperaturregler_milch;
    Zuckerdispenser* zucker;
    Schaeumer* milchschaeumer;
    Bruehgruppe* bruehgruppe;
    Pumpe* wasserpumpe;
    Pumpe* milchpumpe;
    CoffeeState coffeeState;
public:
    bool istFertig() const;

public:
    Programmsteuerung();
    ~Programmsteuerung();
    void setMilchschaeumer(Schaeumer *milchschaeumer);
    void setWasserHeizer(Heizregler* heizer);
    void setMilchHeizer(Heizregler* heizer);
    void setBruehgruppe(Bruehgruppe* gruppe);
    void setWasserpumpe(Pumpe* pumpe);
    void setMilchpumpe(Pumpe* pumpe);
    void setZuckerdispenser(Zuckerdispenser* dispenser);
    void ausfuehren(Kaffeeprogramm *programm);
    void setCurrentState(CoffeeState state);
    bool isBusy() const;
    CoffeeState getCurrentState() const;

public slots:
    void tick();

};

#endif
