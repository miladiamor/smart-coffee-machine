#ifndef PUMPE_H
#define PUMPE_H

class Pumpe{

    private:
        int status;
        bool starten;

    public:
        Pumpe();
        virtual ~Pumpe();
        virtual void pumpeStarten();
        virtual void pumpeStoppen();
        virtual bool istAktiv() const;
};

#endif // PUMPE_H
