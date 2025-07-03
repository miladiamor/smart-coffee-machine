#include <QtTest>

// add necessary includes here
#include "bruehgruppe.h"
#include "programmsteuerung.h"
#include "Heizregler.h"
#include "Pumpe.h"
#include "Zuckerdispenser.h"
#include "Schaeumer.h"
#include "motorsteuerung.h"
#include "klappe.h"
#include "ventil.h"

//MockUps Kaffeeprogramm
float Kaffeeprogramm::getstampfHoehe_mm() const {return 7.0;}
std::vector<int> abgefragteWasserKochhitzen;
std::vector<int> abgefragteMilchKochhitzen;

int Kaffeeprogramm::getKaffeemenge_g() const {return 8;}
int Kaffeeprogramm::getWassermenge_ml() const {return 100;}
int Kaffeeprogramm::getMilchmenge_ml() const {return 150;}

int Kaffeeprogramm::getWasserKochhitze_Cel() const {
    int wert = 95;
    abgefragteWasserKochhitzen.push_back(wert);
    return wert;
}

int Kaffeeprogramm::getMilchKochhitze_Cel() const {
    int wert = 90;
    abgefragteMilchKochhitzen.push_back(wert);
    return wert;
}

bool MitZucker = true;
bool Kaffeeprogramm::getMitZucker() const {return MitZucker;}

//MockUps Motorsteuerung, Ventile und Klappen für die Bruehgruppe
Ventil *globalWasserzufuhr, *globalKaffeezufuhr, *globalTropfstopf;
bool wasserOffen = false;
bool kaffeeOffen = false;
bool tropfOffen = false;

void Ventil::oeffnen() {
    if (this == globalWasserzufuhr) {
        wasserOffen = true;
    } else if (this == globalKaffeezufuhr) {
        kaffeeOffen = true;
    } else if (this == globalTropfstopf) {
        tropfOffen = true;
    }
}

void Ventil::schliessen() {
    if (this == globalWasserzufuhr) {
        wasserOffen = false;
    } else if (this == globalKaffeezufuhr) {
        kaffeeOffen = false;
    } else if (this == globalTropfstopf) {
        tropfOffen = false;
    }
}

bool klappeOffen = {};
void Klappe::oeffnen() {klappeOffen = true;}
void Klappe::schliessen() {klappeOffen = false;}

std::vector<float> hoehen = {};
void Motorsteuerung::stampferAusfahren(float stampfHoehe_mm) {hoehen.push_back(stampfHoehe_mm);}
void Motorsteuerung::tick() {}

// Mockup für die Pumpe
bool wasserpumpeAktiv = false;
bool milchpumpeAktiv = false;
Pumpe *globalWasserpumpe = nullptr;
Pumpe *globalMilchpumpe = nullptr;
void Pumpe::pumpeStarten() {
    if (this == globalMilchpumpe) {
        milchpumpeAktiv = true;
    } else {
        wasserpumpeAktiv = true;
    }
}
void Pumpe::pumpeStoppen() {
    if (this == globalMilchpumpe) {
        milchpumpeAktiv = false;
    } else {
        wasserpumpeAktiv = false;
    }
}

//Mockup für die Heizregler
Heizregler* globalWasserHeizer = nullptr;
Heizregler* globalMilchHeizer = nullptr;
int zielTemperaturWasser = 0;
int zielTemperaturMilch = 0;
bool istReglerAktiv = false;

void Heizregler::temperaturRegeln(int zieltemperatur_Cel){
    if (this == globalWasserHeizer){
        zielTemperaturWasser = zieltemperatur_Cel;
    } else if (this == globalMilchHeizer){
        zielTemperaturMilch = zieltemperatur_Cel;
    }
    istReglerAktiv = true;
}

bool Heizregler::getEingeschaltet() {
    return istReglerAktiv;
}

bool Heizregler::istTemperaturErreicht() const {
    return true;
}

void Heizregler::tick() {}

//Mockup für die Zuckerdispenser
bool ZuckerdispenserAktiv = false;
void Zuckerdispenser::zuckerAuswerfen() {
    ZuckerdispenserAktiv = true;
}
void Zuckerdispenser::ausschalten() {
    ZuckerdispenserAktiv = false;
}
bool Zuckerdispenser::istAktiv() const {
    return ZuckerdispenserAktiv;
}

//Mockup für der Schaeumer
int SchaeumerAktiv = 0;
void Schaeumer::aufschaeumenStarten() {SchaeumerAktiv++;}
void Schaeumer::aufschaeumenStoppen() {SchaeumerAktiv--;}
bool Schaeumer::getEingeschaltet() {return SchaeumerAktiv;}

// Testklasse
class ti_programmsteuerung_bruehgruppe : public QObject
{
    Q_OBJECT

public:
    ti_programmsteuerung_bruehgruppe();
    ~ti_programmsteuerung_bruehgruppe();

private:
    Programmsteuerung* ps;
    Bruehgruppe *bg;
    Kaffeeprogramm *mKp;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testIdleZuHeizen();
    void testHeizenZuKaffe_Zufur();
    void testKaffee_ZufuhrZuWartenaufbruehgruppe();
    void testWartenaufbruehgruppeZuPumping_Water();
    void testPumping_WaterZuPumping_Milk();
    void testPumping_MilkZuZuckerAuswerfen();
    void testZuckerAuswerfenZuZurueck_Setzen();
    void testZurueck_SetzenZuIdle();
};

ti_programmsteuerung_bruehgruppe::ti_programmsteuerung_bruehgruppe() {}

ti_programmsteuerung_bruehgruppe::~ti_programmsteuerung_bruehgruppe() {}

void ti_programmsteuerung_bruehgruppe::initTestCase() {
    ps = new Programmsteuerung();
    bg = new Bruehgruppe();

    mKp = new Kaffeeprogramm();

    // Komponenteninitialisierung für Brühgruppe
    Motorsteuerung mMs;
    globalWasserzufuhr = new Ventil();
    globalKaffeezufuhr = new Ventil();
    globalTropfstopf = new Ventil();

    bg->setMotorsteuerung(&mMs);
    bg->setWasserzufuhr(globalWasserzufuhr);
    bg->setKaffeezufuhr(globalKaffeezufuhr);
    bg->setTropfstopfventil(globalTropfstopf);

    // Komponenteninitialisierung für Programmsteuerung
    Zuckerdispenser mZd;
    Schaeumer mS;
    globalWasserpumpe = new Pumpe();
    globalMilchpumpe = new Pumpe();
    globalMilchHeizer = new Heizregler();
    globalWasserHeizer = new Heizregler();

    ps->setZuckerdispenser(&mZd);
    ps->setMilchschaeumer(&mS);
    ps->setBruehgruppe(bg);
    ps->setWasserpumpe(globalWasserpumpe);
    ps->setMilchpumpe(globalMilchpumpe);
    ps->setMilchHeizer(globalMilchHeizer);
    ps->setWasserHeizer(globalWasserHeizer);
}

void ti_programmsteuerung_bruehgruppe::cleanupTestCase() {}

void ti_programmsteuerung_bruehgruppe::testIdleZuHeizen() {
    ps->ausfuehren(mKp);

    // Programmsteuerung prüfen
    QVERIFY(ps->isBusy());
    ps->tick();
    QCOMPARE(ps->getCurrentState(), Programmsteuerung::CoffeeState::HEIZEN);
    QCOMPARE(zielTemperaturWasser, mKp->getWasserKochhitze_Cel());
    QCOMPARE(zielTemperaturMilch, mKp->getMilchKochhitze_Cel());

    // Brühgruppe prüfen
    QCOMPARE(bg->getState(), WARTEN);
}

void ti_programmsteuerung_bruehgruppe::testHeizenZuKaffe_Zufur() {

}

void ti_programmsteuerung_bruehgruppe::testKaffee_ZufuhrZuWartenaufbruehgruppe() {

}

void ti_programmsteuerung_bruehgruppe::testWartenaufbruehgruppeZuPumping_Water() {

}

void ti_programmsteuerung_bruehgruppe::testPumping_WaterZuPumping_Milk() {

}

void ti_programmsteuerung_bruehgruppe::testPumping_MilkZuZuckerAuswerfen() {

}

void ti_programmsteuerung_bruehgruppe::testZuckerAuswerfenZuZurueck_Setzen() {

}

void ti_programmsteuerung_bruehgruppe::testZurueck_SetzenZuIdle() {

}

QTEST_APPLESS_MAIN(ti_programmsteuerung_bruehgruppe)

#include "tst_ti_programmsteuerung_bruehgruppe.moc"
