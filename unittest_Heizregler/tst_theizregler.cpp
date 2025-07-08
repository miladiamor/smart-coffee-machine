#include <QtTest>
#include "Heizregler.h"

// Heizelemente Mock ups
int aktuelleTemperatur = 20;
int zieltemperatur = 0;
bool heizelementAktiv = false;

Temperatursensor::Temperatursensor() {}
int Temperatursensor::getTemperatur_Cel() const { return aktuelleTemperatur; }
void Temperatursensor::setTemperatur_Cel(int t_cel) { aktuelleTemperatur = t_cel; }

void Heizelemente::einschalten() { heizelementAktiv = true; }
void Heizelemente::ausschalten() { heizelementAktiv = false; }
bool Heizelemente::istEingeschaltet() const { return heizelementAktiv; }


class tHeizregler : public QObject
{
    Q_OBJECT

private:
    Heizregler* heizregler;
    Heizelemente* heizelement;
    Temperatursensor* sensor;

public:
    tHeizregler();
    ~tHeizregler();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_heizenStartetWennZuKalt();
    void test_heizenStopptWennZielErreicht();
};

tHeizregler::tHeizregler() {}

tHeizregler::~tHeizregler() {}

void tHeizregler::initTestCase() {
    heizelement = new Heizelemente();
    sensor = new Temperatursensor();
    heizregler = new Heizregler();

    heizregler->setHeizelement(heizelement);
    heizregler->setTemperatursensor(sensor);
}

void tHeizregler::cleanupTestCase() {
    delete heizregler;
    delete heizelement;
    delete sensor;
}

void tHeizregler::test_heizenStartetWennZuKalt() {
    aktuelleTemperatur = 30;
    zieltemperatur = 80;

    heizregler->temperaturRegeln(zieltemperatur);
    QVERIFY(heizregler->getEingeschaltet());
    QVERIFY(heizelementAktiv);
    QVERIFY(!heizregler->istTemperaturErreicht());
}

void tHeizregler::test_heizenStopptWennZielErreicht() {
    aktuelleTemperatur = 85;
    zieltemperatur = 80;

    heizregler->temperaturRegeln(zieltemperatur);
    heizregler->tick();
    QVERIFY(!heizregler->getEingeschaltet());
    QVERIFY(!heizelementAktiv);
    QVERIFY(heizregler->istTemperaturErreicht());
}

QTEST_APPLESS_MAIN(tHeizregler)

#include "tst_theizregler.moc"
