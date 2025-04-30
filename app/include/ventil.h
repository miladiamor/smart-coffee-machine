#ifndef VENTIL_H
#define VENTIL_H

#include "bruehgruppe.h"
class Ventil
{
public:
    Ventil();
    void oeffnen();
    void schliessen();
    bool getIstOffen();

private:
    bool istOffen();
    Bruehgruppe &bruehG;
};

#endif // VENTIL_H
