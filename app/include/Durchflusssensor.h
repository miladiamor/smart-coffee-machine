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
        float wassermenge_g;

    public:
        Durchflusssensor();
        bool getDurchflussImpuls() const;
        void setDurchflussImpuls(bool impuls);
        void reset();
        float getWassermenge_g() const;
        void addWassermenge_g(float wassermenge_g);
        void setNull();
};

#endif // DURCHFLUSSSENSOR_H
