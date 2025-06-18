#pragma once
#ifndef PROGRAMMSTEUERUNG_H
#define PROGRAMMSTEUERUNG_H

#include <QObject>
#include <QTimer>

enum class SteuerungStates {
    WARTEN,
    FUELLEN,
    ERHITZEN,
    KOCHEN,
    ENTLEEREN,
    PROGRAMM_ABGESCHLOSSEN,
    FEHLER
};

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
    int status;
    int tickCounter;
    Kaffeeprogramm* programm;

    Heizregler *temperaturregler_wasser, *temperaturregler_milch;
    Zuckerdispenser* zucker;
    Schaeumer* milchschaeumer;
    Bruehgruppe* bruehgruppe;
    Pumpesteuerung* steuerung;
    Fuellstandsmessung* messung;
    QTimer *Timer;
    void trigger(SteuerungStates *nextState);

public:
    Programmsteuerung();
    void setMilchschaeumer(Schaeumer *milchschaeumer);
    void ausfuehren(Kaffeeprogramm *programm);
    void tick();

public slots:
           void nextStep();
};

#endif
