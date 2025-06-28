#include <QtTest>
#include <QObject>
#include "Programmsteuerung.h"
#include "kaffeeprogramm.h"
#include "Zuckerdispenser.h"
#include "Pumpe.h"
#include "Heizregler.h"
#include "Schaeumer.h"
#include "bruehgruppe.h"
//#include <vector>
// add necessary includes here

class tProgrammsteuerung : public QObject
{
    Q_OBJECT

public:
    tProgrammsteuerung();
    ~tProgrammsteuerung();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void testStartenFuehrtZuHeizen();
    void testHeizenFuehrtZuKaffeezufuhr();
    void testKaffeezufuhrFuehrtZuWasserpumpen();
    void testWasserpumpenFuehrtZuMilchpumpen();
    void testMilchpumpenFuehrtZuZuckerauswerfen();
    void testZuckerauswerfenFuehrtZuZuruecksetzen();
    void testZuruecksetzenFuehrtZuIdle();

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

tProgrammsteuerung::tProgrammsteuerung() {}
tProgrammsteuerung::~tProgrammsteuerung() {}

void tProgrammsteuerung::init() {
    mPT = new Programmsteuerung();
    mKP = new Kaffeeprogramm();
    mWasserheizer = new Heizregler();
    mMilchheizer = new Heizregler();
    mMP = new Pumpe();
    mWP = new Pumpe();
    mBG = new Bruehgruppe();
    mS  = new Schaeumer();
    mZD = new Zuckerdispenser();

    mBG->setState(WARTEN);
    mBG->setKaffeeprogramm(mKP);
    mPT->setWasserHeizer(mWasserheizer);
    mPT->setMilchHeizer(mMilchheizer);
    mPT->setWasserpumpe(mWP);
    mPT->setMilchpumpe(mMP);
    mPT->setBruehgruppe(mBG);
    mPT->setMilchschaeumer(mS);
    mPT->setZuckerdispenser(mZD);
}

void tProgrammsteuerung::cleanup() {
    delete mPT;
    delete mKP;
    delete mWasserheizer;
    delete mMilchheizer;
    delete mWP;
    delete mMP;
    delete mS;
    delete mZD;
    delete mBG;
}

void tProgrammsteuerung::testStartenFuehrtZuHeizen() {
    mPT->ausfuehren(mKP);
    QVERIFY(mPT->isBusy());
    mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::HEIZEN);
}

void tProgrammsteuerung::testHeizenFuehrtZuKaffeezufuhr() {
    mPT->ausfuehren(mKP);
    mPT->tick();
    //QVERIFY(mBG->getKaffeeprogramm() != nullptr);
    for(int i = 0; i < 100; ++i) mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::KAFFEE_ZUFUHR);
}

void tProgrammsteuerung::testKaffeezufuhrFuehrtZuWasserpumpen() {
    mPT->ausfuehren(mKP);
    for(int i = 0; i < 130; ++i) mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::PUMPING_WATER);
    QVERIFY(mWP->istAktiv());
}

void tProgrammsteuerung::testWasserpumpenFuehrtZuMilchpumpen() {
    testKaffeezufuhrFuehrtZuWasserpumpen();
    for(int i = 0; i < 20; ++i) mPT->tick();
    QVERIFY(!mWP->istAktiv());
    QVERIFY(mMP->istAktiv());
    QVERIFY(mS->getEingeschaltet());
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::PUMPING_MILK);
}

void tProgrammsteuerung::testMilchpumpenFuehrtZuZuckerauswerfen() {
    testWasserpumpenFuehrtZuMilchpumpen();
    for(int i = 0; i < 15; ++i) mPT->tick();
    QVERIFY(!mMP->istAktiv());
    QVERIFY(mZD->istAktiv());
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::ZUCKERAUSWERFEN);
}

void tProgrammsteuerung::testZuckerauswerfenFuehrtZuZuruecksetzen() {
    testMilchpumpenFuehrtZuZuckerauswerfen();
    for(int i = 0; i < 6; ++i) mPT->tick();
    QVERIFY(!mZD->istAktiv());
    QVERIFY(!mS->getEingeschaltet());
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::ZURUECK_SETZEN);
}

void tProgrammsteuerung::testZuruecksetzenFuehrtZuIdle() {
    testZuckerauswerfenFuehrtZuZuruecksetzen();
    mPT->tick();
    QCOMPARE(mPT->getCurrentState(), Programmsteuerung::CoffeeState::IDLE);
    QVERIFY(!mPT->isBusy());
}

void tProgrammsteuerung::initTestCase() {}
void tProgrammsteuerung::cleanupTestCase() {}

QTEST_APPLESS_MAIN(tProgrammsteuerung)
#include "tst_tprogrammsteuerung.moc"
