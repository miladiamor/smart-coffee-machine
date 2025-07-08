#include <QtTest>

#include "motorsteuerung.h"
#include "inkrementalencoder.h"
#include "kolbenmotor.h"
#include "bruehgruppe.h"

// MockUps
Inkrementalencoder::Inkrementalencoder() {}
float pos = 0;
float Inkrementalencoder::getPosition_mm() {return pos;}

Kolbenmotor::Kolbenmotor(QObject *parent) : QObject{parent} {}
bool hoch = false;
bool runter = false;
void Kolbenmotor::hochfahren() {hoch = true;}
void Kolbenmotor::runterfahren() {runter = true;}
void Kolbenmotor::stoppen() {hoch = false; runter = false;}

bool motorAbgeschlossen = false;
void Bruehgruppe::trigger(BruehEvent event) {
    if (event == MOTORABGESCHLOSSEN) {
        motorAbgeschlossen = true;
    }
}
class tmotorsteuerung : public QObject
{
    Q_OBJECT

public:
    tmotorsteuerung();
    ~tmotorsteuerung();

private:
    Bruehgruppe *mBg;
    Kolbenmotor *mKm;
    Inkrementalencoder *mIe;
    Motorsteuerung *ms;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_hochfahren();
    void test_stoppenWennErreicht();
};

tmotorsteuerung::tmotorsteuerung() {}

tmotorsteuerung::~tmotorsteuerung() {}

void tmotorsteuerung::initTestCase() {
    mBg = new Bruehgruppe();
    mKm = new Kolbenmotor();
    mIe = new Inkrementalencoder();
    ms = new Motorsteuerung();

    ms->setBruehgruppe(mBg);
    ms->setInkrementalencoder(mIe);
    ms->setStampfer(mKm);
}

void tmotorsteuerung::cleanupTestCase() {
    delete ms;
    delete mBg;
    delete mKm;
    delete mIe;
}

void tmotorsteuerung::test_hochfahren() {
    ms->stampferAusfahren(7.0);
    QVERIFY(hoch);
    while (1) {
        if(!motorAbgeschlossen) {
            pos += 0.5;
            ms->tick();
        } else {
            break;
        }
    }
    QCOMPARE(pos, 7.0);
}

void tmotorsteuerung::test_stoppenWennErreicht() {
    ms->stampferAusfahren(20);
    pos = 20;
    ms->tick();
    QVERIFY(!runter);
    QVERIFY(!hoch);
}

QTEST_APPLESS_MAIN(tmotorsteuerung)

#include "tst_tmotorsteuerung.moc"
