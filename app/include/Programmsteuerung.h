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

struct ressourcen {
    int wasser;
    int kaffee;
    int milch;
    int zucker;
};

class Programmsteuerung : public QObject {
    Q_OBJECT

private:
    int status;
    Kaffeeprogramm* programm;

    Heizregler* temp_regler;
    Zuckerdispenser* zucker;
    Schaeumer* milchschaeumer;
    Bruehgruppe* bruehgruppe;
    Pumpsteuerung* steuerung;
    Fuellstandsmessung* messung;

    bool ressourcenCheck();

public:
    Programmsteuerung();
    void ausfuehren(int programm);
};

#endif
