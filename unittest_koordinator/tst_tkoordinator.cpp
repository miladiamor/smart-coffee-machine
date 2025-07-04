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
void Display::displayScreen(const QImage&) {
    displayCalled++;
}
QPointF Display::getLastTouch() {
    return forcedTouch;
}
void Display::acceptTouch(QPointF&) {}

// === MOCK Programmsteuerung ===
Programmsteuerung::Programmsteuerung() {}
Programmsteuerung::~Programmsteuerung() {}

void Programmsteuerung::ausfuehren(Kaffeeprogramm*) {
    ausfuehrenCalled = true;
}

bool Programmsteuerung::istFertig() const {
    return true;
}
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
bool Zahlungseinheit::versucheZahlung(Produkt*) {
    return versucheZahlungReturn;
}

// === MOCK Fuellstandsmessung ===
Fuellstandsmessung::Fuellstandsmessung() {}

// ===Implementierung Test

class tkoordinator : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
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
}void tkoordinator::initTestCase() {}

void tkoordinator::cleanupTestCase() {}

void tkoordinator::testWartenZuZuckerwahl() {
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::WARTEN);

    forcedTouch = QPointF(100, 100);
    sut->tick();

    QVERIFY(displayCalled > 0);
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::ZUCKERWAHL);
}

void tkoordinator::testZuckerwahlZuBezahlen() {

    while (sut->getCurrentState() != KoordinatorZustand::ZUCKERWAHL) {
        sut->tick();
    }
    int previousDisplayCalled = displayCalled;
    forcedTouch = QPointF(100, 100); // triggers the transition
    sut->tick();
    QVERIFY(displayCalled > previousDisplayCalled);
    QCOMPARE(sut->getCurrentState(), KoordinatorZustand::BEZAHLEN);
}

