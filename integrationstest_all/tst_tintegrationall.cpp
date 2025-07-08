#include <QtTest>
#include <QPointF>

//includes
#include "Ressourcen.h"
#include "kaffeeprogramm.h"
#include "display.h"
#include "Koordinator.h"
#include "bruehgruppe.h"
#include "programmsteuerung.h"
#include "Heizregler.h"
#include "Pumpe.h"
#include "Zuckerdispenser.h"
#include "Schaeumer.h"
#include "motorsteuerung.h"
#include "klappe.h"
#include "ventil.h"
#include "zahlungseinheit.h"
#include "Fuellstandsmessung.h"

//MockUps Ventile und Klappen für die Bruehgruppe
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

// Mockups für die Motorsteuerung (Motor und InkE)
Kolbenmotor::motorStatus globalMotorStatus = Kolbenmotor::motorStatus::Aus;
Kolbenmotor::Kolbenmotor(QObject *parent) : QObject{parent} {}
void Kolbenmotor::runterfahren() {globalMotorStatus = Kolbenmotor::motorStatus::runterfahren;}
void Kolbenmotor::hochfahren() {globalMotorStatus = Kolbenmotor::motorStatus::hochfahren;}
void Kolbenmotor::stoppen() {globalMotorStatus = Kolbenmotor::motorStatus::Aus;}

float globalStampferPos = 25.0;
Inkrementalencoder::Inkrementalencoder() {}
float Inkrementalencoder::getPosition_mm() {return globalStampferPos;}

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
bool wasserheizerAktiv = false;
bool milchheizerAktiv = false;

void Heizregler::temperaturRegeln(int zieltemperatur_Cel){
    if (this == globalWasserHeizer){
        zielTemperaturWasser = zieltemperatur_Cel;
        wasserheizerAktiv = true;
    } else if (this == globalMilchHeizer){
        zielTemperaturMilch = zieltemperatur_Cel;
        milchheizerAktiv = true;
    }
}

bool Heizregler::getEingeschaltet() {
    if (this == globalWasserHeizer){
        return wasserheizerAktiv;
    } else if (this == globalMilchHeizer){
        return milchheizerAktiv;
    }
    return false;
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

// MOCK Zahlungseinheit
Zahlungseinheit::Zahlungseinheit() {}
void Zahlungseinheit::versucheZahlung(float preis) {}
bool Zahlungseinheit::getZahlungErfolgreich() {return true;}

// MOCK Fuellstandsmessung
bool hatGenugReturn = true;
Fuellstandsmessung::Fuellstandsmessung() {}
bool Fuellstandsmessung::hatGenug(Tankwaage*, int, float) const { return hatGenugReturn; }

class tintegrationall : public QObject
{
    Q_OBJECT

public:
    tintegrationall();
    ~tintegrationall();

private:
    Display *display;
    Koordinator *koordinator;
    Programmsteuerung *programmsteuerung;
    Bruehgruppe *bruehgruppe;
    Motorsteuerung *motorsteuerung;

    Fuellstandsmessung *mFuellstandmessung;
    Zahlungseinheit *mZahlungseinheit;

    Pumpe *mWasserpumpe, *mMilchpumpe;
    Heizregler *mHeizregler;
    Schaeumer *mSchaeumer;
    Zuckerdispenser *mZuckerdispenser;

    Kolbenmotor *mStampfer;
    Inkrementalencoder *mInkrementalencoder;
    Klappe *mEntleer;

    void tickAll();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_milchkaffee();
};

tintegrationall::tintegrationall() {}

tintegrationall::~tintegrationall() {}

void tintegrationall::initTestCase() {
    //zu testende Module initialisieren
    display = new Display();
    koordinator = new Koordinator();
    programmsteuerung = new Programmsteuerung();
    bruehgruppe = new Bruehgruppe();
    motorsteuerung = new Motorsteuerung();

    // Komponenten für Koordinator setzen
    mFuellstandmessung = new Fuellstandsmessung();
    mZahlungseinheit = new Zahlungseinheit();
    koordinator->setzeFuellstandsmessung(mFuellstandmessung);
    koordinator->setzeZahlungseinheit(mZahlungseinheit);
    koordinator->setzeDisplay(display);
    koordinator->setzeProgrammsteuerung(programmsteuerung);

    // Komponenten für Programmsteuerung setzen
    globalWasserpumpe = new Pumpe();
    globalMilchpumpe = new Pumpe();
    globalWasserHeizer = new Heizregler();
    globalMilchHeizer = new Heizregler();
    mZuckerdispenser = new Zuckerdispenser();

    programmsteuerung->setWasserpumpe(globalWasserpumpe);
    programmsteuerung->setMilchpumpe(globalMilchpumpe);
    programmsteuerung->setWasserHeizer(globalWasserHeizer);
    programmsteuerung->setMilchHeizer(globalMilchHeizer);
    programmsteuerung->setBruehgruppe(bruehgruppe);
    programmsteuerung->setZuckerdispenser(mZuckerdispenser);

    // Komponenten für Brühgrupe und Motorsteuerung setzen
    globalKaffeezufuhr = new Ventil();
    globalWasserzufuhr = new Ventil();
    globalTropfstopf = new Ventil();
    mEntleer = new Klappe();
    mInkrementalencoder = new Inkrementalencoder();
    mStampfer = new Kolbenmotor();
    motorsteuerung = new Motorsteuerung();

    motorsteuerung->setStampfer(mStampfer);
    motorsteuerung->setInkrementalencoder(mInkrementalencoder);

    bruehgruppe->setMotorsteuerung(motorsteuerung);
    bruehgruppe->setWasserzufuhr(globalWasserzufuhr);
    bruehgruppe->setKaffeezufuhr(globalKaffeezufuhr);
    bruehgruppe->setTropfstopfventil(globalTropfstopf);
    bruehgruppe->setEntleerklappe(mEntleer);
}

void tintegrationall::cleanupTestCase() {

}

void tintegrationall::tickAll() {
    koordinator->tick();
    programmsteuerung->tick();
    motorsteuerung->tick();
}

void tintegrationall::test_milchkaffee() {
    QPointF pt;
    pt.setX(100);
    pt.setY(100);

    // milchkaffee wird ausgewählt
    display->acceptTouch(pt);
    tickAll();
    QCOMPARE(KoordinatorZustand::ZUCKERWAHL, koordinator->getCurrentState());

    // mit Zucker wählem
    pt = QPointF(50.0, 50.0);
    display->acceptTouch(pt);
    tickAll();
    QCOMPARE(KoordinatorZustand::BEZAHLEN, koordinator->getCurrentState());

    // programmsteuerung geht in Ausführen über
    tickAll();
    QCOMPARE(KoordinatorZustand::AUSFUEHREN, koordinator->getCurrentState());
    tickAll();
    QCOMPARE(programmsteuerung->getCurrentState(), Programmsteuerung::CoffeeState::HEIZEN);
    QCOMPARE(KoordinatorZustand::WARTEN_AUF_FERTIG, koordinator->getCurrentState());

    // HEIZEN zu Kaffezufuhr bzw triggert Kaffeezufuhr
    tickAll();
    QCOMPARE(programmsteuerung->getCurrentState(), Programmsteuerung::CoffeeState::KAFFEE_ZUFUHR);
    QCOMPARE(bruehgruppe->getState(), KAFFEEZUFUHR);
    // hier prüfe ich, dass das Ventil offen sein muss
    QVERIFY(kaffeeOffen);

    // Kaffeezufuhr zu Wartenaufbruehgruppee bzw triggert wartenaufbruehgruppe x
    for (int i = 0; i < 50; i++) tickAll();
    QCOMPARE(programmsteuerung->getCurrentState(), Programmsteuerung::CoffeeState::WARTENAUFBRUEHGRUPPE);
    QCOMPARE(bruehgruppe->getState(), STAMPFEN);
    QVERIFY(!kaffeeOffen);
    QCOMPARE(globalMotorStatus, Kolbenmotor::motorStatus::runterfahren);

    // Bruehrgruppe STAMPFEN zu KOCHEN
    globalStampferPos = 7; tickAll();
    QCOMPARE(bruehgruppe->getState(), KOCHEN);
    QCOMPARE(globalMotorStatus, Kolbenmotor::motorStatus::Aus);
    QVERIFY(wasserOffen);
    QVERIFY(tropfOffen);

    // Programssteuerung WARTENAUFKOCHEN zu PUMPING_WATER
    tickAll();
    QCOMPARE(programmsteuerung->getCurrentState(), Programmsteuerung::CoffeeState::PUMPING_WATER);
    QVERIFY(wasserpumpeAktiv);

    // Pumping water zu pumping milk bzw. triggert Pumping milk x
    for (int i = 0; i < 5; ++i) tickAll();
    QCOMPARE(programmsteuerung->getCurrentState(), Programmsteuerung::CoffeeState::PUMPING_MILK);
    QVERIFY(!wasserpumpeAktiv);
    QVERIFY(milchpumpeAktiv);
    QVERIFY(SchaeumerAktiv > 0);

    // pumping milk zu zuckerauswerfen bzw. triggert Zuckerauswerfen x
    for (int i = 0; i < 15; ++i) tickAll();
    QCOMPARE(programmsteuerung->getCurrentState(), Programmsteuerung::CoffeeState::ZUCKERAUSWERFEN);
    QCOMPARE(bruehgruppe->getState(), ENTLEEREN);
    QVERIFY(!milchpumpeAktiv);
    QVERIFY(!SchaeumerAktiv);
    QVERIFY(ZuckerdispenserAktiv);
    QVERIFY(!wasserOffen);
    QVERIFY(!tropfOffen);
    QVERIFY(klappeOffen);
    QCOMPARE(globalMotorStatus, Kolbenmotor::motorStatus::runterfahren);

    // programsteuerung zuckerauswerfen zu ZURUECKSETZEN
    for (int i = 0; i < 5; ++i) tickAll();
    tickAll();
    QCOMPARE(programmsteuerung->getCurrentState(), Programmsteuerung::CoffeeState::ZURUECK_SETZEN);
    QVERIFY(!programmsteuerung->isBusy());
    QVERIFY(!ZuckerdispenserAktiv);

    // Brühgruppe ENTLEEREN zu WARTEN
    globalStampferPos = 0; tickAll();
    QCOMPARE(bruehgruppe->getState(), ZURUECKSETZEN);
    QVERIFY(!klappeOffen);
    globalStampferPos = MAX_MOTOR_HEIGHT_MM; tickAll();
    QCOMPARE(bruehgruppe->getState(), WARTEN);

    // programmsteuerung ZURUECKSETZEN zu IDLE
    tickAll();
    QCOMPARE(programmsteuerung->getCurrentState(), Programmsteuerung::CoffeeState::IDLE);
    QVERIFY(!programmsteuerung->isBusy());
}

QTEST_APPLESS_MAIN(tintegrationall)

#include "tst_tintegrationall.moc"
