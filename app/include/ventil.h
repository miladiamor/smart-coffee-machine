#ifndef VENTIL_H
#define VENTIL_H

class Ventil
{
public:
    Ventil();
    void oeffnen();
    void schliessen();
    bool getIstOffen();

private:
    bool istOffen();
};

#endif // VENTIL_H
