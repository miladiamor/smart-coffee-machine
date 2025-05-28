#pragma once

#include "Fuellstandsmessung.h"
#include "Kaffeeprogramm.h"
#include "mainwindow.h"
#include "Zahlungseinheit.h"
#include "Programmsteuerung.h"

class Koordinator {
private:
    Fuellstandsmessung *fuellstandmessung;
    Kaffeeprogramm programm;
    MainWindow  *anzeige;
    Zahlungseinheit *zahlung;
    Programmsteuerung * steuerung;
    bool mitZucker;

public:
    Koordinator();
    void setFuellstandsmessung(Fuellstandsmessung *fsm);
    void setAnzeige(MainWindow *anzeige);
    void setZahlung(Zahlungseinheit *zahlung);
    void setSteuerung(Programmsteuerung *steuerung);
    bool bezahlen();

    Kaffeeprogramm* getProgramm();
};
