#ifndef BRUEHGRUPPE_H
#define BRUEHGRUPPE_H

#include <QObject>
#include <QTimer>
#include "ventil.h"
#include "klappe.h"
#include "kolbenmotor.h"
#include "inkrementalencoder.h"
#include "kaffeeprogramm.h"
enum state {WARTEN, ENTLEEREN, STAMPFEN, KOCHBEREIT, KAFFEEZUFUHR, ZURUECKSETZEN};

class Bruehgruppe : public QObject
{
Q_OBJECT
public:
    Bruehgruppe();
    ~Bruehgruppe();
    void entleeren();
    void kaffeeFuellen();
    void trigger(state nextState);

    bool getEntleerklappeOffen();
    bool getWasserzufuhrOffen();
    bool getKaffeezufuhrOffen();
    state getState();
public slots:
    void tick();

private:
    int tickCount;
    state currentState;
    state nextState;
    QTimer sleeper;
    Ventil *tropfstopfventil, *wasserzufuhr, *kaffeezufuhr;
    Klappe *entleerklappe;
    Kolbenmotor *stampfer;
    Inkrementalencoder *inkrementalencoder;
    Kaffeeprogramm *kaffeeprogramm;
};

#endif

