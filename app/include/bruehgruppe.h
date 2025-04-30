#ifndef BRUEHGRUPPE_H
#define BRUEHGRUPPE_H

#include "ventil.h"
#include "klappe.h"
#include "kolbenmotor.h"
#include "inkrementalencoder.h"

class Bruehgruppe
{
    public:
        Bruehgruppe();
        void kaffeePressen(int stampfHoehe_mm);
        void entleeren();
        void tropfstopVentilSchliessen();
        void tropfstopVentilOeffnen();
        void wasserzufuhrOeffnen();
        void wasserzufuhrSchliessen();
        void kaffeepulverHinzufuegen(int menge_g);

        int getStatus();
    private:
        int status;
        Ventil tropfstopfVentil, wasserzufuhr, kaffeeZufuhr;
        Klappe entleerKlappe;
        Kolbenmotor stampfer;
        InkrementalEncoder encoder;
};

#endif // BRUEHGRUPPE_H
