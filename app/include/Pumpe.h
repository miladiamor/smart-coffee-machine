#ifndef PUMPE_H
#define PUMPE_H

class Pumpe{

    private:
        int status;
        bool starten;

    public:
        Pumpe();
        ~Pumpe();
        void pumpeStarten();
        void pumpeStoppen();
        bool istAktiv() const;
};

#endif // PUMPE_H
