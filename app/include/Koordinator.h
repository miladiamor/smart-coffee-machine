#pragma once

#include "Fuellstandsmessung.h"
#include "kaffeeprogramm.h"
#include "mainwindow.h"
#include "zahlungseinheit.h"
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

    Kaffeeprogramm* getAusgewaehltesProgramm() const;
};
