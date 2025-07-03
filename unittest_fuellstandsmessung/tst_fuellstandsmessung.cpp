#include <QObject>
#include <QtTest>

#include "Fuellstandsmessung.h"
#include "Tankwaage.h"
#include "Ressourcen.h"

// === Inject missing Tankwaage methods ===
Tankwaage::Tankwaage(float gewicht_g) : gewicht_g(gewicht_g) {}
float Tankwaage::gewichtPruefen() const { return gewicht_g; }

// === Inject missing Ressourcen setters ===
void Ressourcen::setWassermenge_ml(int ml) { wassermenge_ml = ml; }
void Ressourcen::setMilchmenge_ml(int ml) { milchmenge_ml = ml; }
void Ressourcen::setKaffeemenge_g(int g) { kaffeemenge_g = g; }
void Ressourcen::setZuckermenge_TL(short tl) { zuckermenge_TL = tl; }

// === Inject missing Ressourcen getters ===
int Ressourcen::getWassermenge_ml() const { return wassermenge_ml; }
int Ressourcen::getMilchmenge_ml() const { return milchmenge_ml; }
int Ressourcen::getKaffeemenge_g() const { return kaffeemenge_g; }
short Ressourcen::getZuckermenge_TL() const { return zuckermenge_TL; }

// === The actual test class ===
class tfuellstandsmessung : public QObject
{
    Q_OBJECT

private:
    Fuellstandsmessung* sut;
    Tankwaage* wasser;
    Tankwaage* milch;
    Tankwaage* kaffee;
    Tankwaage* zucker;
    Ressourcen* ressourcen;

private slots:
    void init();
    void cleanup();
    void testUpdateRessourcen();
    void testHatGenug();
};

void tfuellstandsmessung::init() {
    wasser = new Tankwaage(500.0f);   // 500g water
    milch = new Tankwaage(515.0f);    // 515g milk (approx 500ml / density)
    kaffee = new Tankwaage(200.0f);   // 200g coffee
    zucker = new Tankwaage(50.0f);    // 50g sugar
    ressourcen = new Ressourcen();

    sut = new Fuellstandsmessung(wasser, milch, kaffee, zucker, ressourcen);
}

void tfuellstandsmessung::cleanup() {
    delete sut;
    delete wasser;
    delete milch;
    delete kaffee;
    delete zucker;
    delete ressourcen;
}

void tfuellstandsmessung::testUpdateRessourcen() {
    QVERIFY(sut->updateRessourcen());

    QCOMPARE(ressourcen->getWassermenge_ml(), 500);
    QCOMPARE(ressourcen->getMilchmenge_ml(), 500); // approx 515 / 1.03
    QCOMPARE(ressourcen->getKaffeemenge_g(), 200);
    QCOMPARE(ressourcen->getZuckermenge_TL(), static_cast<short>(10)); // 50/5
}

void tfuellstandsmessung::testHatGenug() {
    QVERIFY(sut->hatGenug(wasser, 200));           // true (500 >= 200)
    QVERIFY(!sut->hatGenug(kaffee, 300));          // false (200 < 300)
    QVERIFY(sut->hatGenug(zucker, 5, 5.0f));       // true (50 >= 25)
}

QTEST_APPLESS_MAIN(tfuellstandsmessung)
#include "tst_fuellstandsmessung.moc"
