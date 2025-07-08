#ifndef MUENZROEHRENSPEICHER_H
#define MUENZROEHRENSPEICHER_H

#include "Muenzroehre.h"
#include "Muenzenschieber.h"
#include "MuenzAuswerfer.h"
#include "MuenzEingabeSensor.h"

class Muenzroehrenspeicher {
private:
    Muenzroehre* roehre2Euro;
    Muenzroehre* roehre1Euro;
    Muenzroehre* roehre50Cent;
    Muenzroehre* roehre20Cent;
    Muenzroehre* roehre10Cent;

    Muenzenschieber* schieber;
    MuenzAuswerfer* auswerfer;
    MuenzEingabeSensor *sensor;
public:
    // Standardkonstruktor fuer Unittests
    Muenzroehrenspeicher();

    // Konstruktor mit Abhaengigkeiten
    Muenzroehrenspeicher(Muenzroehre* r2, Muenzroehre* r1, Muenzroehre* r50,
                         Muenzroehre* r20, Muenzroehre* r10,
                         Muenzenschieber* schieber, MuenzAuswerfer* auswerfer);

    void setroehre2Euro(Muenzroehre *roehre2Euro);
    void setroehre1Euro(Muenzroehre *roehre1Euro);
    void setroehre50Cent(Muenzroehre *roehre50Cent);
    void setroehre20Cent(Muenzroehre *roehre20Cent);
    void setroehre10Cent(Muenzroehre *roehre10Cent);
    void setschieber(Muenzenschieber *schieber);
    void setauswerfer(MuenzAuswerfer *auswerfer);
    void setsensor(MuenzEingabeSensor *sensor);

    bool fuegeMuenzeEin(float wert);
    void muenzeAuswerfen(float wert);
    void geldAuswerfen(float betrag); // wirft mehrere Münzen aus
    void tick();
};

#endif
