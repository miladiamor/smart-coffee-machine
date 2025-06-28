#include <QtTest>
#include "Fuellstandsmessung.h"
#include "Tankwaage.h"
#include "Ressourcen.h"

// Test class
class tst_tst_fuellstandsmessung : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testUpdateRessourcen();
    void testHatGenugTrue();
    void testHatGenugFalse();

private:
    Tankwaage *wasser;
    Tankwaage *milch;
    Tankwaage *kaffee;
    Tankwaage *zucker;
    Ressourcen *ressourcen;
    Fuellstandsmessung *fsm;
};

void tst_tst_fuellstandsmessung::init()
{
    wasser = new Tankwaage(200.0f);  // 200g water
    milch = new Tankwaage(103.0f);   // 103g milk (~100ml)
    kaffee = new Tankwaage(50.0f);   // 50g coffee
    zucker = new Tankwaage(15.0f);   // 15g sugar (~3 tsp)
    ressourcen = new Ressourcen();
    fsm = new Fuellstandsmessung(wasser, milch, kaffee, zucker, ressourcen);
}

void tst_tst_fuellstandsmessung::cleanup()
{
    delete fsm;
    delete ressourcen;
    delete wasser;
    delete milch;
    delete kaffee;
    delete zucker;
}

void tst_tst_fuellstandsmessung::testUpdateRessourcen()
{
    QVERIFY(fsm->updateRessourcen());
    QCOMPARE(ressourcen->getWassermenge_ml(), 200);
    QCOMPARE(ressourcen->getMilchmenge_ml(), static_cast<int>(103.0 / 1.03));  // ~100
    QCOMPARE(ressourcen->getKaffeemenge_g(), 50);
    QCOMPARE(ressourcen->getZuckermenge_TL(), static_cast<short>(15 / 5));     // 3
}

void tst_tst_fuellstandsmessung::testHatGenugTrue()
{
    QVERIFY(fsm->hatGenug(wasser, 100));         // has 200
    QVERIFY(fsm->hatGenug(kaffee, 50));          // has 50
    QVERIFY(fsm->hatGenug(zucker, 3, 5));        // needs 15, has 15
}

void tst_tst_fuellstandsmessung::testHatGenugFalse()
{
    QVERIFY(!fsm->hatGenug(wasser, 250));        // needs 250, has 200
    QVERIFY(!fsm->hatGenug(kaffee, 51));         // needs 51, has 50
    QVERIFY(!fsm->hatGenug(zucker, 4, 5));       // needs 20, has 15
}

QTEST_APPLESS_MAIN(tst_tst_fuellstandsmessung)
#include "tst_tst_fuellstandsmessung.moc"
