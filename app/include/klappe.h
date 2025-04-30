#ifndef KLAPPE_H
#define KLAPPE_H

#include "bruehgruppe.h"

class Klappe
{
    public:
        Klappe();
        void oeffnen();
        void schliessen();
        int  getOffen();

    private:
        bool istOffen;
        Bruehgruppe &bruehG;
};

#endif // KLAPPE_H
