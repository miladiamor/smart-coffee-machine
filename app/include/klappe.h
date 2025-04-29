#ifndef KLAPPE_H
#define KLAPPE_H

class Klappe
{
    public:
        Klappe();
        void oeffnen();
        void schliessen();
        int  getOffen();

    private:
        bool istOffen;
};

#endif // KLAPPE_H
