#include "muenzroehrenspeicher.h"
#include <QDebug>

// Konstruktor fuer Unittests
Muenzroehrenspeicher::Muenzroehrenspeicher()
    : roehre2Euro(nullptr), roehre1Euro(nullptr), roehre50Cent(nullptr),
    roehre20Cent(nullptr), roehre10Cent(nullptr),
    schieber(nullptr), auswerfer(nullptr) {}

// Konstruktor mit allen Komponenten
Muenzroehrenspeicher::Muenzroehrenspeicher(Muenzroehre* r2, Muenzroehre* r1, Muenzroehre* r50,
                                           Muenzroehre* r20, Muenzroehre* r10,
                                           Muenzenschieber* schieber, MuenzAuswerfer* auswerfer)
    : roehre2Euro(r2), roehre1Euro(r1), roehre50Cent(r50),
    roehre20Cent(r20), roehre10Cent(r10),
    schieber(schieber), auswerfer(auswerfer) {}

void Muenzroehrenspeicher::setroehre2Euro(Muenzroehre *roehre2Euro)
{
    this->roehre2Euro = roehre2Euro;
}

void Muenzroehrenspeicher::setroehre1Euro(Muenzroehre *roehre1Euro)
{
    this->roehre1Euro = roehre1Euro;
}

void Muenzroehrenspeicher::setroehre50Cent(Muenzroehre *roehre50Cent)
{
    this->roehre50Cent = roehre50Cent;
}

void Muenzroehrenspeicher::setroehre20Cent(Muenzroehre *roehre20Cent)
{
    this->roehre20Cent = roehre20Cent;
}

void Muenzroehrenspeicher::setroehre10Cent(Muenzroehre *roehre10Cent)
{
    this->roehre10Cent = roehre10Cent;
}

void Muenzroehrenspeicher::setschieber(Muenzenschieber *schieber)
{
    this->schieber = schieber;
}

void Muenzroehrenspeicher::setauswerfer(MuenzAuswerfer *auswerfer)
{
    this->auswerfer = auswerfer;
}

void Muenzroehrenspeicher::setsensor(MuenzEingabeSensor *sensor)
{
    this->sensor = sensor;
}


// Gibt false zurueck, wenn Muenze ungueltig oder Zielrohr voll ist.
bool Muenzroehrenspeicher::fuegeMuenzeEin(float wert) {

    Muenzroehre* ziel = nullptr;
    if (wert == 2.0f) ziel = roehre2Euro;
    else if (wert == 1.0f) ziel = roehre1Euro;
    else if (wert == 0.5f) ziel = roehre50Cent;
    else if (wert == 0.2f) ziel = roehre20Cent;
    else if (wert == 0.1f) ziel = roehre10Cent;
    else {
        return false;
    }
    if (ziel->istVoll()) {
        auswerfer->auswerfenMuenze(ziel);
        return false;
    }
    schieber->schiebeMuenzeInRoehre(ziel);
    return true;
}


void Muenzroehrenspeicher::muenzeAuswerfen(float wert) {
    Muenzroehre* quelle = nullptr;

    if (wert == 2.0f) quelle = roehre2Euro;
    else if (wert == 1.0f) quelle = roehre1Euro;
    else if (wert == 0.5f) quelle = roehre50Cent;
    else if (wert == 0.2f) quelle = roehre20Cent;
    else if (wert == 0.1f) quelle = roehre10Cent;
    else return;

    if (quelle->getAnzahl() > 0 ) {
        auswerfer->auswerfenMuenze(quelle);
        quelle->reduziereAnzahl();
    }
}



void Muenzroehrenspeicher::geldAuswerfen(float betrag) {
    const float werte[] = {2.0f, 1.0f, 0.5f, 0.2f, 0.1f};

    for (float wert : werte) {
        Muenzroehre* quelle = nullptr;

        if (wert == 2.0f) quelle = roehre2Euro;
        else if (wert == 1.0f) quelle = roehre1Euro;
        else if (wert == 0.5f) quelle = roehre50Cent;
        else if (wert == 0.2f) quelle = roehre20Cent;
        else if (wert == 0.1f) quelle = roehre10Cent;

        while (betrag >= wert && quelle->getAnzahl() > 0) {
            betrag -= wert;
            muenzeAuswerfen(wert);
            quelle->reduziereAnzahl();
        }
    }
}
