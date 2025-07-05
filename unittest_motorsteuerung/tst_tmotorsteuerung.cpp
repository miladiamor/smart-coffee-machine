#include <QtTest>

// add necessary includes here

class tmotorsteuerung : public QObject
{
    Q_OBJECT

public:
    tmotorsteuerung();
    ~tmotorsteuerung();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

tmotorsteuerung::tmotorsteuerung() {}

tmotorsteuerung::~tmotorsteuerung() {}

void tmotorsteuerung::initTestCase() {}

void tmotorsteuerung::cleanupTestCase() {}

void tmotorsteuerung::test_case1() {}

QTEST_APPLESS_MAIN(tmotorsteuerung)

#include "tst_tmotorsteuerung.moc"
