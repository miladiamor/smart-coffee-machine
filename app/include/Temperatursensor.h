#ifndef TEMPERATURSENSOR_H
#define TEMPERATURSENSOR_H

class Temperatursensor {
private:
    int temperatur_Cel;

public:
    Temperatursensor();                  // Konstruktor
    int getTemperatur_Cel();
    void setTemperatur_Cel(int t) { temperatur_Cel = t; }
};

#endif // TEMPERATURSENSOR_H
