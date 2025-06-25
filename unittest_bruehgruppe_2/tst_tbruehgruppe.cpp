#include <QtTest>
#include "bruehgruppe.h"
#include "ventil.h"
#include "klappe.h"
#include "motorsteuerung.h"
#include "kaffeeprogramm.h"
#include <vector>

//MockUps
int ventilOffen = 0;
void Ventil::oeffnen() {ventilOffen++;}
void Ventil::schliessen() {ventilOffen--;}

int klappeOffen = 0;
void Klappe::oeffnen() {klappeOffen++;}
void Klappe::schliessen() {klappeOffen--;}

float Kaffeeprogramm::getstampfHoehe_mm() const {return 7.0;}

std::vector<float> hoehen = {};
void Motorsteuerung::stampferAusfahren(float stampfHoehe_mm) {hoehen.push_back(stampfHoehe_mm);}
void Motorsteuerung::tick() {}

//Implementierung Test
class tbruehgruppe : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void testWartenZuKaffeezufhur();
    void testKaffeezufuhrZuStampfen();
    void testStampfenZuKochen();
    void testKochenZuEntleeren();
    void testEntleerenZuZuruecksetzen();
    void testZuruecksetzenZuWarten();

private:
    Bruehgruppe *mBG;
    Kaffeeprogramm *mKaffeeprogramm;
    Motorsteuerung *mMotorsteuerung;
    Ventil *mWasserzufuhr, *mKaffeezufuhr, *mTropfstopf;
    Klappe *mEntleer;
};

void tbruehgruppe::init() {
    // Bruehgruppe und Komponenten initialisieren
    mBG = new Bruehgruppe();
    mKaffeeprogramm = new Kaffeeprogramm();
    mWasserzufuhr = new Ventil();
    mKaffeezufuhr = new Ventil();
    mTropfstopf = new Ventil();
    mEntleer = new Klappe();

    // Bruehgruppe die Komponenten übergeben
    mBG->setKaffeeprogramm(mKaffeeprogramm);
    mBG->setMotorsteuerung(mMotorsteuerung);
    mBG->setTropfstopfventil(mTropfstopf);
    mBG->setKaffeezufuhr(mKaffeezufuhr);
    mBG->setWasserzufuhr(mWasserzufuhr);
    mBG->setEntleerklappe(mEntleer);
}

void tbruehgruppe::cleanup() {

}

void tbruehgruppe::initTestCase() {

}

void tbruehgruppe::cleanupTestCase() {
    ventilOffen = 0;
    klappeOffen = 0;
    hoehen.clear();
}

void tbruehgruppe::testWartenZuKaffeezufhur() {
    //Bruehgruppe auf state initialisieren
    mBG->setState(WARTEN);

    QCOMPARE(mBG->getState(), WARTEN);
    QVERIFY(hoehen.size() == 0);

    mBG->trigger(ZUFUHRSTART);
    QCOMPARE(mBG->getState(), KAFFEEZUFUHR);
    QVERIFY(ventilOffen == 1);
}

void tbruehgruppe::testKaffeezufuhrZuStampfen(){
    //Bruehgruppe auf state initialisieren
    mBG->setState(KAFFEEZUFUHR);
    ventilOffen = 1;

    mBG->trigger(ZUFUHRABGESCHLOSSEN);
    QCOMPARE(mBG->getState(), STAMPFEN);
    QVERIFY(ventilOffen == 0);
    QVERIFY(hoehen[0] == 7.0);
}

void tbruehgruppe::testStampfenZuKochen(){
    //Bruehgruppe auf state initialisieren
    mBG->setState(STAMPFEN);

    mBG->trigger(MOTORABGESCHLOSSEN);
    QCOMPARE(mBG->getState(), KOCHEN);
    QVERIFY(ventilOffen == 2);
}

void tbruehgruppe::testKochenZuEntleeren(){
    //Bruehgruppe auf state initialisieren
    mBG->setState(KOCHEN);
    ventilOffen = 2;

    mBG->trigger(KOCHENAUFGEHOERT);
    QCOMPARE(mBG->getState(), ENTLEEREN);
    QVERIFY(klappeOffen == 1);
    QVERIFY(ventilOffen == 0);
    QVERIFY(hoehen[0] == 0);
}

void tbruehgruppe::testEntleerenZuZuruecksetzen(){
    //Bruehgruppe auf state initialisieren
    mBG->setState(ENTLEEREN);
    klappeOffen = 1;

    mBG->trigger(MOTORABGESCHLOSSEN);
    QCOMPARE(mBG->getState(), ZURUECKSETZEN);
    QVERIFY(klappeOffen == 0);
    QVERIFY(hoehen[0] == MAX_MOTOR_HEIGHT_MM);
}

void tbruehgruppe::testZuruecksetzenZuWarten(){
    //Bruehgruppe auf state initialisieren
    mBG->setState(ZURUECKSETZEN);

    mBG->trigger(MOTORABGESCHLOSSEN);
    QCOMPARE(mBG->getState(), WARTEN);
}

QTEST_APPLESS_MAIN(tbruehgruppe)

#include "tst_tbruehgruppe.moc"
