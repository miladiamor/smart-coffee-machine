#include <QtTest>
#include "Koordinator.h"
#include "Programmsteuerung.h"
#include "kaffeeprogramm.h"
#include "Zahlungseinheit.h"
#include "display.h"

// Mock Display to control touches
class MockDisplay : public Display {
private:
    QPointF touchPoint = QPointF(-1, -1);
public:
    void setTouch(const QPointF &point) { touchPoint = point; }
    QPointF getLastTouch() override { return touchPoint; }
    void displayScreen(const QImage &) override {} // Do nothing
};

// Mock Zahlungseinheit to auto-approve payment
class MockZahlungseinheit : public Zahlungseinheit {
public:
    bool versucheZahlung(Produkt *produkt) override { Q_UNUSED(produkt); return true; }
};

// Mock Programmsteuerung to instantly complete
class MockProgrammsteuerung : public Programmsteuerung {
    bool fertig = false;
public:
    void ausfuehren(Kaffeeprogramm *k) override { Q_UNUSED(k); fertig = false; }
    void tick() override { fertig = true; }
    bool istFertig() override { return fertig; }
};

// Test Class
class t_koordinator : public QObject
{
    Q_OBJECT

private:
    Koordinator *k;
    MockDisplay *mockDisplay;
    MockZahlungseinheit *mockZahlung;
    MockProgrammsteuerung *mockProg;

private slots:
    void init() {
        k = new Koordinator();
        mockDisplay = new MockDisplay();
        mockZahlung = new MockZahlungseinheit();
        mockProg = new MockProgrammsteuerung();

        k->setzeDisplay(mockDisplay);
        k->setzeZahlungseinheit(mockZahlung);
        k->setzeProgrammsteuerung(mockProg);
    }

    void cleanup() {
        delete k;
        delete mockDisplay;
        delete mockZahlung;
        delete mockProg;
    }

    void testCappuccinoSelectionToExecution() {
        // Simulate Cappuccino Touch
        mockDisplay->setTouch(QPointF(100, 100)); // top-left -> Cappuccino
        k->tick();
        QCOMPARE(static_cast<int>(k->getState()), static_cast<int>(KoordinatorZustand::ZUCKERWAHL));

        // Simulate Sugar Yes
        mockDisplay->setTouch(QPointF(100, 100)); // top-left -> Sugar yes
        k->tick();
        QCOMPARE(static_cast<int>(k->getState()), static_cast<int>(KoordinatorZustand::BEZAHLEN));

        // Simulate Pay Touch
        mockDisplay->setTouch(QPointF(150, 350)); // in payment area
        k->tick();
        QCOMPARE(static_cast<int>(k->getState()), static_cast<int>(KoordinatorZustand::AUSFUEHREN));

        // Tick until finished
        k->tick();
        QCOMPARE(static_cast<int>(k->getState()), static_cast<int>(KoordinatorZustand::WARTEN));
    }
};

QTEST_APPLESS_MAIN(t_koordinator)
#include "tst_tst_koordinator.moc"
