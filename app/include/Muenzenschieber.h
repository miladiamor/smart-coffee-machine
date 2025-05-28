#ifndef MUENZENSCHIEBER_H
#define MUENZENSCHIEBER_H

#include "Muenzroehre.h"

class Muenzenschieber {
private:
    Muenzroehre* aktiveMuenzroehre;

public:
    Muenzenschieber();

    // Wähle Zielröhre und simuliere Schiebemechanismus
    void schiebeMuenzeInRoehre(Muenzroehre* muenzroehre);
};

#endif // MUENZENSCHIEBER_H

