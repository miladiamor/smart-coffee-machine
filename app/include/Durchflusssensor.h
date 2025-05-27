#ifndef DURCHFLUSSSENSOR_H
#define DURCHFLUSSSENSOR_H

#include <QObject>
class Pumpesteuerung;

class Durchflusssensor : public QObject
{
    Q_OBJECT
    private:
        bool durchflussImpuls;
        int impulsCount;

    public:
        Durchflusssensor();
        bool getDurchflussImpuls() const;
        void setDurchflussImpuls(bool impuls);

        int getImpulsCount() const;
        void incrementImpuls();


};

#endif // DURCHFLUSSSENSOR_H
