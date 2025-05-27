#pragma once

#include "Display.h"
#include "Fuellstandsmessung.h"
#include "Kaffeeprogramm.h"

class Koordinator {
private:
    Display* display;
    Fuellstandsmessung* fsm;
    Kaffeeprogramm* ausgewaehltesProgramm;
    bool mitMilch;
    bool mitZucker;

public:
    Koordinator(Display* display, Fuellstandsmessung* fsm);
    void auswahlAnzeigen();
    void nachMilchFragen();
    void nachZuckerFragen();
    bool bezahlen();
    Kaffeeprogramm* getAusgewaehltesProgramm() const;
};
