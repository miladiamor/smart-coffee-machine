#pragma once
//#include "bruehgruppe.h"

class Klappe
{
    public:
        Klappe();
        void oeffnen();
        void schliessen();
        int  getOffen();

    private:
        bool istOffen;
        //Bruehgruppe &bruehG;
};

