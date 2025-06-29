#include <QtTest>
#include <QObject>
#include "Programmsteuerung.h"
#include "kaffeeprogramm.h"
#include "Zuckerdispenser.h"
#include "Pumpe.h"
#include "Heizregler.h"
#include "Schaeumer.h"
#include "bruehgruppe.h"
#include <vector>

// Mockup für die Pumpe
int PumpeAktiv = 0;
void Pumpe::pumpeStarten() {PumpeAktiv++;}
void Pumpe::pumpeStoppen() {PumpeAktiv--;}

// Mockup für die Kaffeeprogramm
std::vector<int> abgefragteWasserKochhitzen;
std::vector<int> abgefragteMilchKochhitzen;
int Kaffeeprogramm::getKaffeemenge_g() const {return 20;}
int Kaffeeprogramm::getWassermenge_ml() const {return 10;}
int Kaffeeprogramm::getMilchmenge_ml() const {return 15;}
int Kaffeeprogramm::getWasserKochhitze_Cel() const {
    int wert = 85;
    abgefragteWasserKochhitzen.push_back(wert);
    return wert;
}
int Kaffeeprogramm::getMilchKochhitze_Cel() const {
    int wert = 40;
    abgefragteMilchKochhitzen.push_back(wert);
    return wert;
}
bool MitZucker = true;
bool Kaffeeprogramm::getMitZucker() const {return MitZucker;}

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

//Mockup für die Bruehgruppe
BruehState bruehState = WARTEN;
void Bruehgruppe::trigger(BruehEvent event) {
    if (event == ZUFUHRSTART) {
        bruehState = KAFFEEZUFUHR;
    } else if (event == ZUFUHRABGESCHLOSSEN) {
        bruehState = STAMPFEN;
    } else if (event == KOCHENAUFGEHOERT) {
        bruehState = WARTEN;
    }
}
BruehState Bruehgruppe::getState(){return bruehState;}

// Implementierung Test
class tProgrammsteuerung : public QObject
{
    Q_OBJECT

/*public:
    tProgrammsteuerung();
    ~tProgrammsteuerung();*/

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void testIdleZuHeizen();
    void testHeizenZuKaffe_Zufur();
    void testKaffee_ZufuhrZuWartenaufbruehgruppe();
    void testWartenaufbruehgruppeZuPumping_Water();
    void testPumping_WaterZuPumping_Milk();
    void testPumping_MilkZuZuckerAuswerfen();
    void testZuckerAuswerfenZuZurueck_Setzen();
    void testZurueck_SetzenZuIdle();

private:
    Programmsteuerung* mPT;
    Kaffeeprogramm* mKP;
    Heizregler* mWasserheizer;
    Heizregler* mMilchheizer;
    Pumpe* mMP;
    Pumpe* mWP;
    Bruehgruppe* mBG;
    Schaeumer* mS;
    Zuckerdispenser* mZD;
};

/*tProgrammsteuerung::tProgrammsteuerung() {}
tProgrammsteuerung::~tProgrammsteuerung() {}*/

void tProgrammsteuerung::init() {
    mPT = new Programmsteuerung();
    mKP = new Kaffeeprogramm();
    mWasserheizer = new Heizregler();
    mMilchheizer = new Heizregler();
    globalWasserHeizer = mWasserheizer;
    globalMilchHeizer = mMilchheizer;
    mMP = new Pumpe();
    mWP = new Pumpe();
    mBG = new Bruehgruppe();
    mS  = new Schaeumer();
    mZD = new Zuckerdispenser();

    //mBG->setState(WARTEN);
    //mBG->setKaffeeprogramm(mKP);
    mPT->setWasserHeizer(mWasserheizer);
    mPT->setMilchHeizer(mMilchheizer);
    mPT->setWasserpumpe(mWP);
    mPT->setMilchpumpe(mMP);
    mPT->setBruehgruppe(mBG);
    mPT->setMilchschaeumer(mS);
    mPT->setZuckerdispenser(mZD);
}

void tProgrammsteuerung::cleanup() {
    PumpeAktiv = 0;
    MitZucker = true;
    zielTemperaturWasser = 0;
    zielTemperaturMilch = 0;
    istReglerAktiv = false;
    ZuckerdispenserAktiv = false;
    SchaeumerAktiv = 0;
    bruehState = WARTEN;
    abgefragteWasserKochhitzen.clear();
    abgefragteMilchKochhitzen.clear();

}

void tProgrammsteuerung::initTestCase() {}

void tProgrammsteuerung::cleanupTestCase() {}

void tProgrammsteuerung::testIdleZuHeizen()
{
    mPT->ausfuehren(mKP);
    QVERIFY(mPT->isBusy());
    mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::HEIZEN);
    QCOMPARE(zielTemperaturWasser, mKP->getWasserKochhitze_Cel());
    QCOMPARE(zielTemperaturMilch, mKP->getMilchKochhitze_Cel());
    QVERIFY(istReglerAktiv);
}

void tProgrammsteuerung::testHeizenZuKaffe_Zufur()
{
    testIdleZuHeizen();
    mPT->tick(); //Kaffeezufuhr
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::KAFFEE_ZUFUHR);
    QCOMPARE(bruehState, KAFFEEZUFUHR);
}

void tProgrammsteuerung::testKaffee_ZufuhrZuWartenaufbruehgruppe()
{
    testHeizenZuKaffe_Zufur();
    int ticks = static_cast<int>(mKP->getKaffeemenge_g() / 0.3);
    for (int i = 0; i < ticks + 1; ++i) mPT->tick();
    //bruehState = STAMPFEN;
    //mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::WARTENAUFBRUEHGRUPPE);
    QCOMPARE(bruehState, STAMPFEN);
}

void tProgrammsteuerung::testWartenaufbruehgruppeZuPumping_Water() {
    testKaffee_ZufuhrZuWartenaufbruehgruppe();
    bruehState = KOCHEN;
    mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::PUMPING_WATER);
    QCOMPARE(PumpeAktiv, 1);  // Wasserpumpe aktiv
}


void tProgrammsteuerung::testPumping_WaterZuPumping_Milk() {
    testWartenaufbruehgruppeZuPumping_Water();
    int ticks = static_cast<int>(mKP->getWassermenge_ml() / 10);
    for (int i = 0; i < ticks; ++i) mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::PUMPING_MILK);
    QCOMPARE(PumpeAktiv, 1); // Milchpumpe +1, Wasserpumpe -1
    QCOMPARE(SchaeumerAktiv, 1);
}

void tProgrammsteuerung::testPumping_MilkZuZuckerAuswerfen() {
    testPumping_WaterZuPumping_Milk();
    int ticks = static_cast<int>(mKP->getMilchmenge_ml() / 10);
    for (int i = 0; i < ticks; ++i) mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::ZUCKERAUSWERFEN);
    QVERIFY(ZuckerdispenserAktiv);
}

void tProgrammsteuerung::testZuckerAuswerfenZuZurueck_Setzen() {
    testPumping_MilkZuZuckerAuswerfen();
    for (int i = 0; i < 5; ++i) mPT->tick(); // getMitZucker() == true -> 5 Ticks
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::ZURUECK_SETZEN);
    QVERIFY(!ZuckerdispenserAktiv);
    bruehState = WARTEN;
    mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::IDLE);
    QVERIFY(!mPT->isBusy());
}

void tProgrammsteuerung::testZurueck_SetzenZuIdle() {
    testZuckerAuswerfenZuZurueck_Setzen();
}

QTEST_APPLESS_MAIN(tProgrammsteuerung)
#include "tst_tprogrammsteuerung.moc"
