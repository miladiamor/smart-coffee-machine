#ifndef TEMPERATURSENSOR_H
#define TEMPERATURSENSOR_H

class Temperatursensor {
private:
    int temperatur_Cel;

public:
    Temperatursensor();
    int getTemperatur_Cel() const;
    void setTemperatur_Cel(int t_cel);
};

#endif // TEMPERATURSENSOR_H
