#ifndef PUMPE_H
#define PUMPE_H
#include <QObject>

class Pumpe : public QObject{
    Q_OBJECT

    private:
        bool ist_Aktiv;

    public:
        Pumpe() : ist_Aktiv(0){}
        void pumpeStarten();
        void pumpeStoppen();
        bool get_Aktiv();

};

#endif // PUMPE_H
