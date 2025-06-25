#include <QtTest>

// add necessary includes here

class tprogrammsteuerung : public QObject
{
    Q_OBJECT

public:
    tprogrammsteuerung();
    ~tprogrammsteuerung();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

tprogrammsteuerung::tprogrammsteuerung() {}

tprogrammsteuerung::~tprogrammsteuerung() {}

void tprogrammsteuerung::initTestCase() {}

void tprogrammsteuerung::cleanupTestCase() {}

void tprogrammsteuerung::test_case1() {}

QTEST_APPLESS_MAIN(tprogrammsteuerung)

#include "tst_tprogrammsteuerung.moc"
