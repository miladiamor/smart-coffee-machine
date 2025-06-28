#ifndef PUMPE_H
#define PUMPE_H
#include <QObject>

class Pumpe : public QObject{
    Q_OBJECT

    private:
        //int status;
        bool starten;

    public:
        Pumpe();
        ~Pumpe();
        void pumpeStarten();
        void pumpeStoppen();
        bool istAktiv() const;
};

#endif // PUMPE_H
