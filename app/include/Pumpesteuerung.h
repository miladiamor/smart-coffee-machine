#ifndef PUMPESTEUERUNG_H
#define PUMPESTEUERUNG_H

#include <QObject>
#include <QTimer>

class Pumpe;
class Durchflusssensor;

enum class Pumpesteuerungstates{
    IDLE,
    PUMPING_WATER,
    PUMPING_MILK,
    PUMPING_COMPLETE,
    ERROR
};

class Pumpesteuerung : public QObject
{
    Q_OBJECT
    private:
        Pumpesteuerungstates currentState;
        Pumpe *wasserpumpe, *milchpumpe;
        Durchflusssensor *wasserzaehler, *milchzaehler;
        int targetamount_ml;
        void setState(Pumpesteuerungstates newState);

    public:
        Pumpesteuerung(Pumpe *wasserpumpe, Pumpe *milchpumpe, Durchflusssensor *wasserzaehler, Durchflusssensor *milchzaehler);
        //void pumpen(float wassermenge);
        Pumpesteuerungstates getState() const;

    public slots:
        void startPumpingWater(int menge_mil);
        void startPumpingMilk(int menge_mil);
        void tick();

    signals:
        void pumpingFinished();
        void fehler(const QString &message);


/*
    private:

        void setWasserpumpe(Pumpe* pump);
        void setMilchpumpe(Pumpe* pump);
        void setWasserzaehler(Durchflusssensor* sensor);
        void setMilchzaehler(Durchflusssensor* sensor);
        void mypumpe1(int wassermenge);
        void mypumpe2(int milchmenge);
        void tick();


    private:
        void trigger(Pumpesteuerungstates nextstate);

*/
};

#endif // PUMPESTEUERUNG_H
