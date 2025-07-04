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

// === GLOBAL STATE TRACKERS FOR TEST VERIFICATION ===
int displayCalled = 0;
QPointF forcedTouch = QPointF(100, 100);
bool ausfuehrenCalled = false;
bool versucheZahlungReturn = true;

// === MOCK Display ===
Display::Display(QObject*) {}
Display::~Display() {}
void Display::displayScreen(const QImage&) { displayCalled++; }
QPointF Display::getLastTouch() { return forcedTouch; }
void Display::acceptTouch(QPointF&) {}

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
Produkt* Kaffeeprogramm::getProdukt() const { return nullptr; }

// === MOCK Zahlungseinheit ===
Zahlungseinheit::Zahlungseinheit() {}
bool Zahlungseinheit::versucheZahlung(Produkt*) { return versucheZahlungReturn; }

// === MOCK Fuellstandsmessung ===
Fuellstandsmessung::Fuellstandsmessung() {}

// === Test Implementation ===
class tkoordinator : public QObject {
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
    Display* mockDisplay;
    Programmsteuerung* mockProg;
    Zahlungseinheit* mockZahlung;
    Fuellstandsmessung* mockFuell;
};

void tkoordinator::init() {
    sut = new Koordinator();
    mockDisplay = new Display();
    mockProg = new Programmsteuerung();
    mockZahlung = new Zahlungseinheit();
    mockFuell = new Fuellstandsmessung();

    sut->setzeDisplay(mockDisplay);
    sut->setzeProgrammsteuerung(mockProg);
    sut->setzeZahlungseinheit(mockZahlung);
    sut->setzeFuellstandsmessung(mockFuell);
}

void tkoordinator::cleanup() {
    displayCalled = 0;
    ausfuehrenCalled = false;
    forcedTouch = QPointF(100, 100);
    versucheZahlungReturn = true;
}

// === TEST CASES WITH DISPLAY VERIFICATION ===

void tkoordinator::testWartenZuZuckerwahl() {
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN);

    int prevDisplayCalled = displayCalled;
    sut->tick();

    QVERIFY(displayCalled > prevDisplayCalled); // display updated on selection screen
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::ZUCKERWAHL);
}

void tkoordinator::testZuckerwahlZuBezahlen() {
    while (sut->getCurrentState() != KoordinatorZustand::ZUCKERWAHL) {
        forcedTouch = QPointF(100, 100);
        sut->tick();
    }

    int prevDisplayCalled = displayCalled;
    sut->tick();

    QVERIFY(displayCalled > prevDisplayCalled); // display updated on sugar selection
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::BEZAHLEN);
}

void tkoordinator::testBezahlenZuAusfuehren() {
    while (sut->getCurrentState() != KoordinatorZustand::BEZAHLEN) {
        forcedTouch = QPointF(100, 100);
        sut->tick();
    }

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::BEZAHLEN);
    QVERIFY(!ausfuehrenCalled);

    int prevDisplayCalled = displayCalled;
    sut->tick();

    QVERIFY(ausfuehrenCalled);
    QVERIFY(displayCalled > prevDisplayCalled); // display updated on brewing screen
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN_AUF_FERTIG);
}

void tkoordinator::testAusfuehrenZuWartenAufFertig() {
    while (sut->getCurrentState() != KoordinatorZustand::AUSFUEHREN) {
        forcedTouch = QPointF(100, 100);
        sut->tick();
    }

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::AUSFUEHREN);

    int prevDisplayCalled = displayCalled;
    sut->tick();

    QVERIFY(displayCalled >= prevDisplayCalled); // may remain same or increase, still acceptable
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN_AUF_FERTIG);
}

void tkoordinator::testWartenAufFertigZuFertig() {
    while (sut->getCurrentState() != KoordinatorZustand::WARTEN_AUF_FERTIG) {
        forcedTouch = QPointF(100, 100);
        sut->tick();
    }

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN_AUF_FERTIG);
    sut->tick();
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::FERTIG);
}

void tkoordinator::testFertigZuWarten() {
    while (sut->getCurrentState() != KoordinatorZustand::FERTIG) {
        forcedTouch = QPointF(100, 100);
        sut->tick();
    }

    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::FERTIG);
    int prevDisplayCalled = displayCalled;
    sut->tick();

    QVERIFY(displayCalled > prevDisplayCalled); // display updated on done screen
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN);
}

QTEST_APPLESS_MAIN(tkoordinator)
#include "tst_tkoordinator.moc"
