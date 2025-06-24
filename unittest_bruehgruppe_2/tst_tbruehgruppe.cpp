#include <QtTest>

#include <QtTest>
#include "bruehgruppe.h"
#include "ventil.h"
#include "kolbenmotor.h"
#include "kaffeeprogramm.h"
#include <QVector>

class FakeProgramm : public Kaffeeprogramm
{
public:
    virtual ~FakeProgramm() = default;
    float getstampfHoehe_mm() const override { return 6; }   // arbitrary test value
};

class FakeMotorsteuerung : public Motorsteuerung
{
public:
    FakeMotorsteuerung() : hoehen() {}
    virtual ~FakeMotorsteuerung() = default;
    QVector<float> hoehen;
    void stampferAusfahren(float stampfhoehe_mm) override {hoehen.append(stampfhoehe_mm);}
    void hoehenLeeren() {hoehen.clear();}
};

class tbruehgruppe : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

private:
    FakeProgramm *fprogramm;
    FakeMotorsteuerung *fmotorstr;
    Bruehgruppe *bg;
    Ventil *fwasserzufuhr, *fkaffeezufuhr, *ftropfstopf;
    Klappe *fentleerklappe;
};

void tbruehgruppe::init() {
    fprogramm = new FakeProgramm();
    fmotorstr = new FakeMotorsteuerung();
    fwasserzufuhr = new Ventil();
    fkaffeezufuhr = new Ventil();
    ftropfstopf = new Ventil();
    fentleerklappe = new Klappe();
}

void tbruehgruppe::cleanup() {
    delete bg;
    delete fprogramm;
    delete fmotorstr;
    delete fwasserzufuhr;
    delete fkaffeezufuhr;
    delete ftropfstopf;
    delete fentleerklappe;
}

void tbruehgruppe::initTestCase() {
    bg = new Bruehgruppe();
    bg->setKaffeeprogramm(fprogramm);
    bg->setMotorsteuerung(fmotorstr);
    bg->setTropfstopfventil(ftropfstopf);
    bg->setKaffeezufuhr(fkaffeezufuhr);
    bg->setWasserzufuhr(fwasserzufuhr);
    bg->setEntleerklappe(fentleerklappe);
}

void tbruehgruppe::cleanupTestCase() {
    fmotorstr->hoehenLeeren();
    delete bg;
}

void tbruehgruppe::test_case1() {
    QCOMPARE(bg->getState(), WARTEN);
    QVERIFY(fmotorstr->hoehen.length() == 0);

    bg->trigger(ZUFUHRSTART);
    QCOMPARE(bg->getState(), KAFFEEZUFUHR);
    QVERIFY(fkaffeezufuhr->get_ist_offen());

    bg->trigger(ZUFUHRABGESCHLOSSEN);
    QCOMPARE(bg->getState(), STAMPFEN);
    QVERIFY(!fkaffeezufuhr->get_ist_offen());
    QVERIFY(fmotorstr->hoehen[0] == 6);

    bg->trigger(MOTORABGESCHLOSSEN);
    QCOMPARE(bg->getState(), KOCHEN);
    QVERIFY(ftropfstopf->get_ist_offen());
    QVERIFY(fwasserzufuhr->get_ist_offen());

    bg->trigger(KOCHENAUFGEHOERT);
    QCOMPARE(bg->getState(), ENTLEEREN);
    QVERIFY(!ftropfstopf->get_ist_offen());
    QVERIFY(!fwasserzufuhr->get_ist_offen());
    QVERIFY(fentleerklappe->get_ist_offen());
    QVERIFY(fmotorstr->hoehen[1] == 0);

    bg->trigger(MOTORABGESCHLOSSEN);
    QCOMPARE(bg->getState(), ZURUECKSETZEN);
    QVERIFY(!fentleerklappe->get_ist_offen());
    QVERIFY(fmotorstr->hoehen[2] == MAX_MOTOR_HEIGHT_MM);

    bg->trigger(MOTORABGESCHLOSSEN);
    QCOMPARE(bg->getState(), WARTEN);


}

QTEST_APPLESS_MAIN(tbruehgruppe)

#include "tst_tbruehgruppe.moc"
