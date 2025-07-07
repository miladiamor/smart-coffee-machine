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
bool versucheZahlungReturn = true;
Zahlungseinheit::Zahlungseinheit() {}
bool Zahlungseinheit::versucheZahlung(float preis) { return versucheZahlungReturn; }

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

    Kolbenmotor *stampfer;
    Inkrementalencoder *inkrementalencoder;
private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_milchkaffee();
};

tintegrationall::tintegrationall() {}

tintegrationall::~tintegrationall() {}

void tintegrationall::initTestCase() {
    display = new Display();
    koordinator = new Koordinator();
    programmsteuerung = new Programmsteuerung();
    bruehgruppe = new Bruehgruppe();
    motorsteuerung = new Motorsteuerung();

    Fuellstandsmessung mFuellstandmessung;
}

void tintegrationall::cleanupTestCase() {}

void tintegrationall::test_milchkaffee() {
    QPointF pt;
    pt.setX(100);
    pt.setY(100);

}

QTEST_APPLESS_MAIN(tintegrationall)

#include "tst_tintegrationall.moc"
