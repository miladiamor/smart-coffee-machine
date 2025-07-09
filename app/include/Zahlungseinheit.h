#pragma once

#include <QObject>
#include "Muenzroehrenspeicher.h"
#include "MuenzEingabeSensor.h"
#include "MuenzAuswerfer.h"
#include "Display.h"

class Zahlungseinheit : public QObject
{
    Q_OBJECT
private:
    bool zahlungAktiv = false;
    bool zahlungErfolgreich = false;
    float gesamterEinwurf = 0.0f;
    float preis = 0.0f;

    Muenzroehrenspeicher* speicherVerwaltung = nullptr;
    MuenzEingabeSensor* sensor = nullptr;
    MuenzAuswerfer* auswerfer = nullptr;
    Display* display = nullptr;

public:

    Zahlungseinheit(QObject *parent = nullptr) : QObject{parent} {}

    bool getZahlungErfolgreich();


    void versucheZahlung(float preis);


    void zahlungAbbrechen();


    void setDisplay(Display* display);
    void setTestZahlungAktiv(bool aktiv);
    void setMuenzroehrenspeicher(Muenzroehrenspeicher *muenzroehrenspeicher);
    void setMuenzEingabeSensor(MuenzEingabeSensor *muenzeingabesensor);
    void setMuenzAuswerfer(MuenzAuswerfer *muenzauswerfer);

public slots:
    void tick();
};
