#include <QtTest>
#include "koordinator.h"
#include <QImage>
#include <QPointF>

// ====== Mock Flags ======
static bool paymentShouldSucceed = true;
static bool brewingFinished = false;
static QPointF mockTouch(-1, -1);

// ====== Mock Classes ======

// Mock Display
class MockDisplay : public Display {
public:
    MockDisplay() : Display(nullptr) {}
    QPointF getLastTouch() { return mockTouch; }
    void displayScreen(const QImage &) {} // No-op
};

// Mock Zahlungseinheit
class MockZahlungseinheit : public Zahlungseinheit {
public:
    MockZahlungseinheit() : Zahlungseinheit(nullptr, nullptr, nullptr) {}
    bool versucheZahlung(Produkt *) { return paymentShouldSucceed; }
};

// Mock Programmsteuerung
class MockProgrammsteuerung : public Programmsteuerung {
public:
    MockProgrammsteuerung() : Programmsteuerung() {}
    void ausfuehren(Kaffeeprogramm *) {} // No-op
    void tick() {} // No-op
    bool istFertig() const { return brewingFinished; }
};

// ====== Test Class ======
class tkoordinator : public QObject {
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void initTestCase();        // REQUIRED by QtTest
    void cleanupTestCase();     // REQUIRED by QtTest

    void testWartenZuZuckerwahl();
    void testZuckerwahlZuBezahlen();
    void testBezahlenZuAusfuehren();
    void testAusfuehrenZuWarten();

private:
    Koordinator *koordinator;
    MockDisplay *display;
    MockZahlungseinheit *zahlungseinheit;
    MockProgrammsteuerung *programmsteuerung;
};

// ====== Setup & Teardown ======
void tkoordinator::init() {
    koordinator = new Koordinator();
    display = new MockDisplay();
    zahlungseinheit = new MockZahlungseinheit();
    programmsteuerung = new MockProgrammsteuerung();

    koordinator->setzeDisplay(display);
    koordinator->setzeZahlungseinheit(zahlungseinheit);
    koordinator->setzeProgrammsteuerung(programmsteuerung);

    // Reset flags
    mockTouch = QPointF(-1, -1);
    paymentShouldSucceed = true;
    brewingFinished = false;
}

void tkoordinator::cleanup() {
    delete koordinator;
    delete display;
    delete zahlungseinheit;
    delete programmsteuerung;
}

void tkoordinator::initTestCase() {}         // REQUIRED by QtTest
void tkoordinator::cleanupTestCase() {}      // REQUIRED by QtTest

// ====== Tests ======

void tkoordinator::testWartenZuZuckerwahl() {
    QVERIFY(koordinator->getZustand() == KoordinatorZustand::WARTEN);

    mockTouch = QPointF(100, 100); // triggers waehleCappuccino
    koordinator->tick();

    QCOMPARE(koordinator->getZustand(), KoordinatorZustand::ZUCKERWAHL);
}

void tkoordinator::testZuckerwahlZuBezahlen() {
    // WARTEN → ZUCKERWAHL
    mockTouch = QPointF(100, 100);
    koordinator->tick();
    QCOMPARE(koordinator->getZustand(), KoordinatorZustand::ZUCKERWAHL);

    // ZUCKERWAHL → BEZAHLEN
    mockTouch = QPointF(100, 100); // triggers waehleZucker(true)
    koordinator->tick();
    QCOMPARE(koordinator->getZustand(), KoordinatorZustand::BEZAHLEN);
}

void tkoordinator::testBezahlenZuAusfuehren() {
    // WARTEN → ZUCKERWAHL
    mockTouch = QPointF(100, 100);
    koordinator->tick();
    // ZUCKERWAHL → BEZAHLEN
    mockTouch = QPointF(100, 100);
    koordinator->tick();

    QCOMPARE(koordinator->getZustand(), KoordinatorZustand::BEZAHLEN);

    // BEZAHLEN → AUSFUEHREN
    paymentShouldSucceed = true;
    mockTouch = QPointF(150, 350); // triggers payment
    koordinator->tick();

    QCOMPARE(koordinator->getZustand(), KoordinatorZustand::AUSFUEHREN);
}

void tkoordinator::testAusfuehrenZuWarten() {
    // WARTEN → ZUCKERWAHL
    mockTouch = QPointF(100, 100);
    koordinator->tick();
    // ZUCKERWAHL → BEZAHLEN
    mockTouch = QPointF(100, 100);
    koordinator->tick();
    // BEZAHLEN → AUSFUEHREN
    paymentShouldSucceed = true;
    mockTouch = QPointF(150, 350);
    koordinator->tick();

    QCOMPARE(koordinator->getZustand(), KoordinatorZustand::AUSFUEHREN);

    // AUSFUEHREN → WARTEN
    brewingFinished = true;
    koordinator->tick();

    QCOMPARE(koordinator->getZustand(), KoordinatorZustand::WARTEN);
}

QTEST_APPLESS_MAIN(tkoordinator)
#include "tst_koordinator.moc"
