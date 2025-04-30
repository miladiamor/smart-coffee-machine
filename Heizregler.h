#ifndef HEIZREGLER_H
#define HEIZREGLER_H

class Heizregler {
private:
    int zieltemperatur_Cel;
    Temperatursensor *sensor;
    Heizelemente *heizen;

public:
    Heizregler();

    void temperaturRegeln(int Zieltemperatur_Cel);
    void regelnStoppen();
    
};

#endif // HEIZREGLER_HPP
