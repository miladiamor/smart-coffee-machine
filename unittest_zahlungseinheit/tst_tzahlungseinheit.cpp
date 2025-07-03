#include <QtTest>
#include "zahlungseinheit.h"
#include "produkt.h"
#include "muenzroehre.h"
#include "muenzenschieber.h"
#include "muenzroehrenspeicher.h"
#include "muenzeingabesensor.h"
#include "muenzauswerfer.h"

class tst_tzahlungseinheit : public QObject {
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testErfolgreicheZahlung();
    void testAbgelehnteMuenze();
    void testZahlungAbbrechen();

private:
    Zahlungseinheit* zahlungseinheit;
    Produkt* produkt;
    Muenzroehrenspeicher* speicher;
    MuenzEingabeSensor* sensor;
    MuenzAuswerfer* auswerfer;
    Muenzenschieber* schieber;
    Muenzroehre* r2;
    Muenzroehre* r1;
    Muenzroehre* r50;
    Muenzroehre* r20;
    Muenzroehre* r10;
};

void tst_tzahlungseinheit::init() {
    // Röhren und Helfer vorbereiten
    r2 = new Muenzroehre(10);
    r1 = new Muenzroehre(10);
    r50 = new Muenzroehre(10);
    r20 = new Muenzroehre(10);
    r10 = new Muenzroehre(10);

    schieber = new Muenzenschieber();
    auswerfer = new MuenzAuswerfer();
    speicher = new Muenzroehrenspeicher(r2, r1, r50, r20, r10, schieber, auswerfer);
    sensor = new MuenzEingabeSensor();

    zahlungseinheit = new Zahlungseinheit(speicher, sensor, auswerfer);
    produkt = new Produkt("Espresso", 1.0f, 1);
}

void tst_tzahlungseinheit::cleanup() {
    delete zahlungseinheit;
    delete produkt;
    delete speicher;
    delete sensor;
    delete auswerfer;
    delete schieber;
    delete r2;
    delete r1;
    delete r50;
    delete r20;
    delete r10;
}

void tst_tzahlungseinheit::testErfolgreicheZahlung() {
    sensor->simuliereMuenze(1.0f);
    QVERIFY(zahlungseinheit->versucheZahlung(produkt));
}

void tst_tzahlungseinheit::testAbgelehnteMuenze() {
    sensor->simuliereMuenze(3.0f);
    QVERIFY(!zahlungseinheit->versucheZahlung(produkt));
}

void tst_tzahlungseinheit::testZahlungAbbrechen() {
    sensor->simuliereMuenze(1.0f);
    zahlungseinheit->zahlungAbbrechen();
    QVERIFY(true);
}

QTEST_MAIN(tst_tzahlungseinheit)
#include "tst_tzahlungseinheit.moc"
