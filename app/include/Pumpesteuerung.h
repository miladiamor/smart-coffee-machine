#ifndef PUMPESTEUERUNG_H
#define PUMPESTEUERUNG_H

class Pumpe;
class Durchflusssensor;

class Pumpesteuerung
{

    private:
        float menge_mil;
        Pumpe *wasserpumpe, *milchpumpe;
        Durchflusssensor *wasserzaehler, *milchzaehler;


    public:
        Pumpesteuerung();
        void pumpen(float wassermenge);



};

#endif // PUMPESTEUERUNG_H
