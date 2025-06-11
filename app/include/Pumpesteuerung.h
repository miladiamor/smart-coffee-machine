#ifndef PUMPESTEUERUNG_H
#define PUMPESTEUERUNG_H

#include <QObject>
#include <QTimer>

class Pumpe;
class Durchflusssensor;

class Pumpesteuerung : public QObject
{
    Q_OBJECT
    private:
        QTimer *pumpen;
        float menge_mil;
        Pumpe *wasserpumpe, *milchpumpe;
        Durchflusssensor *wasserzaehler, *milchzaehler;


    public:
        Pumpesteuerung(Pumpe *wasserpumpe, Pumpe *milchpumpe, Durchflusssensor *wasserzaehler, Durchflusssensor *milchzaehler);
        //void pumpen(float wassermenge);
    public slots:
        void mypumpe1(float wassermenge);
        void mypumpe2(float milchmenge);


};

#endif // PUMPESTEUERUNG_H
