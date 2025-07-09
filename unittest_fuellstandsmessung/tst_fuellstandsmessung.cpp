#include <QObject>
#include <QtTest>
#include "Fuellstandsmessung.h"
#include "Tankwaage.h"
#include "Ressourcen.h"

Tankwaage::Tankwaage(float gewicht_g) : gewicht_g(gewicht_g) {}
float Tankwaage::gewichtPruefen() const { return gewicht_g; }

void Ressourcen::setWassermenge_ml(int ml) { wassermenge_ml = ml; }
void Ressourcen::setMilchmenge_ml(int ml) { milchmenge_ml = ml; }
void Ressourcen::setKaffeemenge_g(int g) { kaffeemenge_g = g; }
void Ressourcen::setZuckermenge_TL(short tl) { zuckermenge_TL = tl; }

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
    wasser = new Tankwaage(500.0f);
    milch = new Tankwaage(515.0f);
    kaffee = new Tankwaage(200.0f);
    zucker = new Tankwaage(50.0f);
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
    QCOMPARE(ressourcen->getMilchmenge_ml(), 515);
    QCOMPARE(ressourcen->getKaffeemenge_g(), 200);
    QCOMPARE(ressourcen->getZuckermenge_TL(), static_cast<short>(50));
}

void tfuellstandsmessung::testHatGenug() {
    QVERIFY(sut->hatGenug(wasser, 200));
    QVERIFY(!sut->hatGenug(kaffee, 300));
    QVERIFY(sut->hatGenug(zucker, 5, 5.0f));
}

QTEST_APPLESS_MAIN(tfuellstandsmessung)
#include "tst_fuellstandsmessung.moc"
