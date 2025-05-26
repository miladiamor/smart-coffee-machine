#pragma once
#ifndef PROGRAMMSTEUERUNG_H
#define PROGRAMMSTEUERUNG_H

#include <QObject>

class Schaeumer;
class Zuckerdispenser;
class Bruehgruppe;
class Heizregler;
class Pumpsteuerung;
class Fuellstandsmessung;
class Kaffeeprogramm;

class Programmsteuerung : public QObject {
    Q_OBJECT

private:
    int status;
    Kaffeeprogramm* programm;

    Heizregler *temperaturregler_wasser, *temperaturregler_milch;
    Zuckerdispenser* zucker;
    Schaeumer* milchschaeumer;
    Bruehgruppe* bruehgruppe;
    Pumpsteuerung* steuerung;
    Fuellstandsmessung* messung;

public:
    Programmsteuerung();
    void setMilchschaeumer(Schaeumer *milchschaeumer);
    void ausfuehren(Kaffeeprogramm *programm);
};

#endif
