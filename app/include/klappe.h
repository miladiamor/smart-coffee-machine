#ifndef KLAPPE_H
#define KLAPPE_H

class Bruehgruppe;

class Klappe
{
    public:
        Klappe();
        void oeffnen();
        void schliessen();
        int  get_ist_offen();

    private:
        bool ist_offen;
};

#endif
