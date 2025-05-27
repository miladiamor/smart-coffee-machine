#pragma once

#include "Fuellstandsmessung.h"
#include "Kaffeeprogramm.h"

class Koordinator {
private:
    Fuellstandsmessung* fsm;
    Kaffeeprogramm* ausgewaehltesProgramm;
    bool mitMilch;
    bool mitZucker;

public:
    Koordinator(Fuellstandsmessung* fsm);
    void auswahlAnzeigen();
    void nachMilchFragen();
    void nachZuckerFragen();
    bool bezahlen();
    Kaffeeprogramm* getAusgewaehltesProgramm() const;
};
