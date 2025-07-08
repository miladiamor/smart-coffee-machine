#ifndef MOTORSTEUERUNG_H
#define MOTORSTEUERUNG_H

#include <QObject>
#include "inkrementalencoder.h"
#include "kolbenmotor.h"
class Motorsteuerung;
#include "bruehgruppe.h"

#define MAX_MOTOR_HEIGHT_MM 20

class Motorsteuerung : public QObject
{
    Q_OBJECT
public:
    Motorsteuerung(QObject *parent = nullptr) : QObject{parent} {}
    void stampferAusfahren(float stampfhoehe_mm);

    void setBruehgruppe(Bruehgruppe *bruehgruppe);
    void setInkrementalencoder(Inkrementalencoder *inkrementalencoder);
    void setStampfer(Kolbenmotor *stampfer);

    float getStampfhoehe_mm() {return stampfhoehe_mm;}
public slots:
    void tick();

private:
    bool eingeschaltet = false;
    float position_mm;
    float stampfhoehe_mm;
    Bruehgruppe *bruehgruppe;
    Inkrementalencoder *inkrementalencoder;
    Kolbenmotor *stampfer;
};

#endif // MOTORSTEUERUNG_H
