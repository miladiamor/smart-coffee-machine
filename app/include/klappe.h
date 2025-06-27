#ifndef KLAPPE_H
#define KLAPPE_H

#include <QObject>
class Bruehgruppe;

class Klappe : public QObject
{
    Q_OBJECT
    public:
        Klappe() : ist_offen(false) {}
        void oeffnen();
        void schliessen();
        int  get_ist_offen();

    private:
        bool ist_offen;
};

#endif
