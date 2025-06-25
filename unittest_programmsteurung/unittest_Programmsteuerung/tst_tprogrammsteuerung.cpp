#include <QtTest>

#include <QtTest>
#include <QObject>

#include "Programmsteuerung.h"
#include "kaffeeprogramm.h"
#include "Heizregler.h"
#include "Pumpe.h"
#include "Schaeumer.h"
#include "bruehgruppe.h"
#include "Zuckerdispenser.h"

class FakeHeizregler : public Heizregler {
public:
    bool temperaturRegelnAufgerufen = false;
    bool temperaturErreicht = false;
    int zielTemperatur = 0;

    void temperaturRegeln(int ziel_temp_Cel) override {
        temperaturRegelnAufgerufen = true;
        zielTemperatur = ziel_temp_Cel;
    }
    bool istTemperaturErreicht() const override {
        return temperaturErreicht;
    }
    void updateTemperatur() override { }
};


class FakePumpe : public Pumpe {
public:
    bool gestartet = false;
    bool gestoppt = false;

    void pumpeStarten() override { gestartet = true; }
    void pumpeStoppen() override { gestoppt = true; }
};

class FakeBruehgruppe : public Bruehgruppe {
public:
    bool triggerAufgerufen = false;
    Bruehgruppe letzterTrigger;

    Bruehgruppe getState() const override { return WARTEN; } // Always return a predictable state
    void trigger(BruehgruppeState zustand) override {
        triggerAufgerufen = true;
        letzterTrigger = zustand;
    }
};

class FakeSchaeumer : public Schaeumer {
public:
    bool gestartet = false;
    bool gestoppt = false;
    void aufschaeumenStarten() override { gestartet = true; }
    void aufschaeumenStoppen() override { gestoppt = true; }
};

class FakeZuckerdispenser : public Zuckerdispenser {
public:
    bool auswerfenAufgerufen = false;
    bool ausschaltenAufgerufen = false;
    void zuckerAuswerfen() override { auswerfenAufgerufen = true; }
    void ausschalten() override { ausschaltenAufgerufen = true; }
};

class tprogrammsteuerung : public QObject
{
    Q_OBJECT

public:
    tprogrammsteuerung();
    ~tprogrammsteuerung();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

tprogrammsteuerung::tprogrammsteuerung() {}

tprogrammsteuerung::~tprogrammsteuerung() {}

void tprogrammsteuerung::initTestCase() {}

void tprogrammsteuerung::cleanupTestCase() {}

void tprogrammsteuerung::test_case1() {}

QTEST_APPLESS_MAIN(tprogrammsteuerung)

#include "tst_tprogrammsteuerung.moc"
