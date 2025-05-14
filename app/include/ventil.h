#ifndef VENTIL_H
#define VENTIL_H

class Ventil
{
public:
    Ventil();
    void oeffnen();
    void schliessen();
    bool get_ist_offen();

private:
    bool ist_offen;
};

#endif
