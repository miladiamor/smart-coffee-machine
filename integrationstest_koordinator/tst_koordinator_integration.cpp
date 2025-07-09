#include <QtTest>
#include <QObject>
#include <QPointF>
#include <QImage>

#include "Koordinator.h"
#include "Display.h"
#include "Programmsteuerung.h"
#include "Zahlungseinheit.h"
#include "Fuellstandsmessung.h"
#include "Kaffeeprogramm.h"
#include "Ressourcen.h"
#include "Tankwaage.h"


// === GLOBAL STATE TRACKERS FOR TEST VERIFICATION ===
bool ausfuehrenCalled = false;
bool versucheZahlungReturn = true;

// === MOCK Programmsteuerung ===
Programmsteuerung::Programmsteuerung() {}
Programmsteuerung::~Programmsteuerung() {}
void Programmsteuerung::ausfuehren(Kaffeeprogramm*) { ausfuehrenCalled = true; }
bool Programmsteuerung::istFertig() const { return true; }
void Programmsteuerung::tick() {}

// === MOCK Kaffeeprogramm ===
Kaffeeprogramm::Kaffeeprogramm(Ressourcen) {}
void Kaffeeprogramm::setKaffeemenge_g(int) {}
void Kaffeeprogramm::setMilchmenge_ml(int) {}
void Kaffeeprogramm::setWassermenge_ml(int) {}
void Kaffeeprogramm::setWasserKochhitze_Cel(int) {}
void Kaffeeprogramm::setMilchKochhitze_Cel(int) {}
void Kaffeeprogramm::setMitZucker(bool) {}
void Kaffeeprogramm::setStampfhoehe_mm(float) {}
Produkt* Kaffeeprogramm::getProdukt() const { return nullptr; }
int Kaffeeprogramm::getKaffeemenge_g() const { return 10; }
int Kaffeeprogramm::getMilchmenge_ml() const { return 20; }
int Kaffeeprogramm::getWassermenge_ml() const { return 30; }


// === MOCK Zahlungseinheit ===
void Zahlungseinheit::versucheZahlung(float preis) {}
bool Zahlungseinheit::getZahlungErfolgreich() {return true;}
void Zahlungseinheit::tick() {}
// === Test Implementation ===
class tkoordinator_display : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {}
    void cleanupTestCase() {}
    void init();
    void cleanup();
    void testWartenZuZuckerwahl();
    void testZuckerwahlZuBezahlen();
    void testBezahlenZuAusfuehren();
    void testAusfuehrenZuWartenAufFertig();
    void testWartenAufFertigZuFertig();
    void testFertigZuWarten();

private:
    Koordinator* sut;
    Display* display;
    Programmsteuerung* mockProg;
    Zahlungseinheit* mockZahlung;
    Tankwaage* wasserTank;
    Tankwaage* milchTank;
    Tankwaage* kaffeeTank;
    Tankwaage* zuckerTank;
    Ressourcen* ressourcen;
    Fuellstandsmessung* fuellstand;

};

void tkoordinator_display::init() {
    sut = new Koordinator();
    display = new Display();
    mockProg = new Programmsteuerung();
    mockZahlung = new Zahlungseinheit();


    ressourcen = new Ressourcen();
    wasserTank = new Tankwaage(1000.0f);
    milchTank = new Tankwaage(1000.0f);
    kaffeeTank = new Tankwaage(500.0f);
    zuckerTank = new Tankwaage(200.0f);

    fuellstand = new Fuellstandsmessung(wasserTank, milchTank, kaffeeTank, zuckerTank, ressourcen);

    sut->setzeDisplay(display);
    sut->setzeProgrammsteuerung(mockProg);
    sut->setzeZahlungseinheit(mockZahlung);
    sut->setzeFuellstandsmessung(fuellstand);
}


void tkoordinator_display::cleanup() {
    ausfuehrenCalled = false;
    versucheZahlungReturn = true;
}

// === TEST CASES WITH DISPLAY VERIFICATION ===

void tkoordinator_display::testWartenZuZuckerwahl() {
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN);

    QSignalSpy spy(display, &Display::updateDisplay);
    QVERIFY(spy.isValid());

    // Inject touch to trigger transition
    QPointF simulatedTouch(100, 100);
    display->acceptTouch(simulatedTouch);

    // Before tick, assert resources are sufficient for transition
    QVERIFY(fuellstand->hatGenug(wasserTank, 50, 1.0f));
    QVERIFY(fuellstand->hatGenug(milchTank, 150, 1.0f));
    QVERIFY(fuellstand->hatGenug(kaffeeTank, 15, 1.0f));

    sut->tick();

    QVERIFY(spy.count() > 0);
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::ZUCKERWAHL);
}



void tkoordinator_display::testZuckerwahlZuBezahlen() {
    // Bring SUT to ZUCKERWAHL
    while (sut->getCurrentState() != KoordinatorZustand::ZUCKERWAHL) {
        QPointF simulatedTouch(100, 100);
        display->acceptTouch(simulatedTouch);
        sut->tick();
    }

    QSignalSpy spy(display, &Display::updateDisplay);
    QVERIFY(spy.isValid());

    // Simulate touch to select sugar option
    QPointF simulatedTouch(100, 100);
    display->acceptTouch(simulatedTouch);


    QVERIFY(fuellstand->hatGenug(zuckerTank, 5, 1.0f));

    sut->tick();

    QVERIFY(spy.count() > 0);
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::BEZAHLEN);
}




void tkoordinator_display::testBezahlenZuAusfuehren() {
    while (sut->getCurrentState() != KoordinatorZustand::BEZAHLEN) {
        QPointF simulatedTouch(100, 100);
        display->acceptTouch(simulatedTouch);
        sut->tick();
    }

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::BEZAHLEN);
    QVERIFY(!ausfuehrenCalled);
    versucheZahlungReturn = true;

    QSignalSpy spy(display, &Display::updateDisplay);
    QVERIFY(spy.isValid());

    // Provide user interaction for transition
    QPointF simulatedTouch(100, 100);
    display->acceptTouch(simulatedTouch);
    sut->tick();

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::AUSFUEHREN);
    QVERIFY(!ausfuehrenCalled);

    // Next tick triggers ausfuehren
    sut->tick();

    QVERIFY(ausfuehrenCalled);
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN_AUF_FERTIG);
}


void tkoordinator_display::testAusfuehrenZuWartenAufFertig() {
    while (sut->getCurrentState() != KoordinatorZustand::AUSFUEHREN) {
        QPointF simulatedTouch(100, 100);
        display->acceptTouch(simulatedTouch);
        sut->tick();
    }

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::AUSFUEHREN);

    QSignalSpy spy(display, &Display::updateDisplay);
    QVERIFY(spy.isValid());

    sut->tick();

    QVERIFY(spy.count() > 0); // display updated during AUSFUEHREN tick
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN_AUF_FERTIG);
}


void tkoordinator_display::testWartenAufFertigZuFertig() {
    while (sut->getCurrentState() != KoordinatorZustand::WARTEN_AUF_FERTIG) {
        QPointF simulatedTouch(100, 100);
        display->acceptTouch(simulatedTouch);
        sut->tick();
    }

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN_AUF_FERTIG);

    QSignalSpy spy(display, &Display::updateDisplay);
    QVERIFY(spy.isValid());

    sut->tick();

    QVERIFY(spy.count() > 0);
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::FERTIG);
}


void tkoordinator_display::testFertigZuWarten() {
    while (sut->getCurrentState() != KoordinatorZustand::FERTIG) {
        QPointF simulatedTouch(100, 100);
        display->acceptTouch(simulatedTouch);
        sut->tick();
    }

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::FERTIG);


    // Correct connection to the parameterized signal
    QSignalSpy spy(display, SIGNAL(updateDisplay(QImage)));
    QVERIFY(spy.isValid());


    sut->tick();



    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN);
}


QTEST_APPLESS_MAIN(tkoordinator_display)
#include "tst_koordinator_integration.moc"
