#ifndef MUENZENSCHIEBER_H
#define MUENZENSCHIEBER_H

#include "Muenzroehre.h"

class Muenzenschieber {
private:
    Muenzroehre* aktiveMuenzroehre;

public:
    Muenzenschieber();


    void schiebeMuenzeInRoehre(Muenzroehre* muenzroehre);
};

#endif

