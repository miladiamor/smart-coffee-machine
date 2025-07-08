#ifndef MUENZENSCHIEBER_H
#define MUENZENSCHIEBER_H

#include "Muenzroehre.h"
#include "MuenzEingabeSensor.h"

class Muenzenschieber {
private:
    Muenzroehre *aktiveMuenzroehre;
    MuenzEingabeSensor *sensor;

public:
    Muenzenschieber();
    void schiebeMuenzeInRoehre(Muenzroehre* muenzroehre);
};

#endif
