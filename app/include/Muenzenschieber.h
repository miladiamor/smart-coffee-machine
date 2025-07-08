#ifndef MUENZENSCHIEBER_H
#define MUENZENSCHIEBER_H

#include "Muenzroehre.h"

class Muenzenschieber {
private:
    Muenzroehre* aktiveMuenzroehre;

public:
    Muenzenschieber();  //  Standardkonstruktor vorhanden
    void schiebeMuenzeInRoehre(Muenzroehre* muenzroehre);
};

#endif
