#ifndef VENTIL_H
#define VENTIL_H

#include <QObject>

class Ventil : public QObject
{
    Q_OBJECT
public:
    Ventil() : ist_offen(0) {}
    void oeffnen();
    void schliessen();
    bool get_ist_offen();

private:
    bool ist_offen;
};

#endif
