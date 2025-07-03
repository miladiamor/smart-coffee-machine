#include <QtTest>
#include <QObject>
#include <QImage>
#include <QString>
#include <QPointF>

// ======== State Definitions ========
enum class KoordinatorZustand {
    WARTEN,
    ZUCKERWAHL,
    BEZAHLEN,
    BRUEHEN,
    WARTEN_AUF_FERTIG,
    FERTIG
};

// ======== Global Test Flags ========
QString lastDisplayedPath = "";
bool touchDetected = false;
QString requestedPathForTest = "";

// ======== Mock Classes ========
class MockDisplay {
public:
    QPointF getLastTouch() {
        return touchDetected ? QPointF(50, 50) : QPointF(-1, -1);
    }
    void displayScreen(const QImage &) {
        lastDisplayedPath = requestedPathForTest;
    }
};

class MockProgrammsteuerung {
public:
    bool istFertig() const { return true; }
};

class MockZahlungseinheit {
public:
    bool versucheZahlung(int) { return true; }
};

class MockFuellstandsmessung {
public:
    bool hatGenug(int) { return true; }
};

// ======== MockKoordinator replicating transitions ========
class MockKoordinator {
private:
    KoordinatorZustand zustand = KoordinatorZustand::WARTEN;
    MockDisplay* display = nullptr;
    MockProgrammsteuerung* steuerung = nullptr;
    MockZahlungseinheit* zahlung = nullptr;
    MockFuellstandsmessung* fuellstand = nullptr;

public:
    void setzeDisplay(MockDisplay* d) { display = d; }
    void setzeProgrammsteuerung(MockProgrammsteuerung* p) { steuerung = p; }
    void setzeZahlungseinheit(MockZahlungseinheit* z) { zahlung = z; }
    void setzeFuellstandsmessung(MockFuellstandsmessung* f) { fuellstand = f; }

    KoordinatorZustand getCurrentState() const { return zustand; }

    void tick() {
        if (zustand == KoordinatorZustand::WARTEN) {
            requestedPathForTest = ":/images/selection.png";
            display->displayScreen(QImage());
            if (display->getLastTouch().x() >= 0) {
                zustand = KoordinatorZustand::ZUCKERWAHL;
            }
        } else if (zustand == KoordinatorZustand::ZUCKERWAHL) {
            requestedPathForTest = ":/images/payment.png";
            display->displayScreen(QImage());
            if (display->getLastTouch().x() >= 0) {
                zustand = KoordinatorZustand::BEZAHLEN;
            }
        } else if (zustand == KoordinatorZustand::BEZAHLEN) {
            requestedPathForTest = ":/images/brewing.png";
            display->displayScreen(QImage());
            zustand = KoordinatorZustand::BRUEHEN;
        } else if (zustand == KoordinatorZustand::BRUEHEN) {
            requestedPathForTest = ":/images/waiting.png";
            display->displayScreen(QImage());
            zustand = KoordinatorZustand::WARTEN_AUF_FERTIG;
        } else if (zustand == KoordinatorZustand::WARTEN_AUF_FERTIG) {
            if (steuerung->istFertig()) {
                requestedPathForTest = ":/images/ready.png";
                display->displayScreen(QImage());
                zustand = KoordinatorZustand::FERTIG;
            }
        } else if (zustand == KoordinatorZustand::FERTIG) {
            requestedPathForTest = ":/images/selection.png";
            display->displayScreen(QImage());
            zustand = KoordinatorZustand::WARTEN;
        }
    }
};

// ======== Test Class ========
class tKoordinator : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {}
    void cleanupTestCase() {}

    void init() {
        lastDisplayedPath = "";
        touchDetected = false;
        requestedPathForTest = "";
    }

    void cleanup() {}

    void testInitialState();
    void testWartenToZuckerwahl();
    void testZuckerwahlToBezahlen();
    void testBezahlenToBruehen();
    void testBruehenToWartenAufFertig();
    void testWartenAufFertigToFertig();
    void testFertigToWarten(); // NEW
};

void tKoordinator::testInitialState() {
    MockKoordinator k;
    MockDisplay d;
    MockProgrammsteuerung p;
    MockZahlungseinheit z;
    MockFuellstandsmessung f;
    k.setzeDisplay(&d); k.setzeProgrammsteuerung(&p); k.setzeZahlungseinheit(&z); k.setzeFuellstandsmessung(&f);
    k.tick();
    QCOMPARE(k.getCurrentState(), KoordinatorZustand::WARTEN);
    QCOMPARE(lastDisplayedPath, QString(":/images/selection.png"));
}

void tKoordinator::testWartenToZuckerwahl() {
    MockKoordinator k;
    MockDisplay d;
    MockProgrammsteuerung p;
    MockZahlungseinheit z;
    MockFuellstandsmessung f;
    k.setzeDisplay(&d); k.setzeProgrammsteuerung(&p); k.setzeZahlungseinheit(&z); k.setzeFuellstandsmessung(&f);
    touchDetected = true;
    k.tick();
    QCOMPARE(k.getCurrentState(), KoordinatorZustand::ZUCKERWAHL);
    QCOMPARE(lastDisplayedPath, QString(":/images/selection.png"));
}

void tKoordinator::testZuckerwahlToBezahlen() {
    MockKoordinator k;
    MockDisplay d;
    MockProgrammsteuerung p;
    MockZahlungseinheit z;
    MockFuellstandsmessung f;
    k.setzeDisplay(&d); k.setzeProgrammsteuerung(&p); k.setzeZahlungseinheit(&z); k.setzeFuellstandsmessung(&f);
    touchDetected = true; k.tick();
    touchDetected = true; k.tick();
    QCOMPARE(k.getCurrentState(), KoordinatorZustand::BEZAHLEN);
    QCOMPARE(lastDisplayedPath, QString(":/images/payment.png"));
}

void tKoordinator::testBezahlenToBruehen() {
    MockKoordinator k;
    MockDisplay d;
    MockProgrammsteuerung p;
    MockZahlungseinheit z;
    MockFuellstandsmessung f;
    k.setzeDisplay(&d); k.setzeProgrammsteuerung(&p); k.setzeZahlungseinheit(&z); k.setzeFuellstandsmessung(&f);
    touchDetected = true; k.tick();
    touchDetected = true; k.tick();
    k.tick();
    QCOMPARE(k.getCurrentState(), KoordinatorZustand::BRUEHEN);
    QCOMPARE(lastDisplayedPath, QString(":/images/brewing.png"));
}

void tKoordinator::testBruehenToWartenAufFertig() {
    MockKoordinator k;
    MockDisplay d;
    MockProgrammsteuerung p;
    MockZahlungseinheit z;
    MockFuellstandsmessung f;
    k.setzeDisplay(&d); k.setzeProgrammsteuerung(&p); k.setzeZahlungseinheit(&z); k.setzeFuellstandsmessung(&f);
    touchDetected = true; k.tick();
    touchDetected = true; k.tick();
    k.tick();
    k.tick();
    QCOMPARE(k.getCurrentState(), KoordinatorZustand::WARTEN_AUF_FERTIG);
    QCOMPARE(lastDisplayedPath, QString(":/images/waiting.png"));
}

void tKoordinator::testWartenAufFertigToFertig() {
    MockKoordinator k;
    MockDisplay d;
    MockProgrammsteuerung p;
    MockZahlungseinheit z;
    MockFuellstandsmessung f;
    k.setzeDisplay(&d); k.setzeProgrammsteuerung(&p); k.setzeZahlungseinheit(&z); k.setzeFuellstandsmessung(&f);
    touchDetected = true; k.tick();
    touchDetected = true; k.tick();
    k.tick();
    k.tick();
    k.tick();
    QCOMPARE(k.getCurrentState(), KoordinatorZustand::FERTIG);
    QCOMPARE(lastDisplayedPath, QString(":/images/ready.png"));
}

void tKoordinator::testFertigToWarten() {
    MockKoordinator k;
    MockDisplay d;
    MockProgrammsteuerung p;
    MockZahlungseinheit z;
    MockFuellstandsmessung f;
    k.setzeDisplay(&d); k.setzeProgrammsteuerung(&p); k.setzeZahlungseinheit(&z); k.setzeFuellstandsmessung(&f);
    touchDetected = true; k.tick();
    touchDetected = true; k.tick();
    k.tick();
    k.tick();
    k.tick();
    k.tick();
    QCOMPARE(k.getCurrentState(), KoordinatorZustand::WARTEN);
    QCOMPARE(lastDisplayedPath, QString(":/images/selection.png"));
}

// ======== Test Runner ========
QTEST_APPLESS_MAIN(tKoordinator)
#include "tst_tkoordinator.moc"
