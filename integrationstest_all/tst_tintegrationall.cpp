#include <QtTest>

// add necessary includes here

class tintegrationall : public QObject
{
    Q_OBJECT

public:
    tintegrationall();
    ~tintegrationall();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_milchkaffee();
};

tintegrationall::tintegrationall() {}

tintegrationall::~tintegrationall() {}

void tintegrationall::initTestCase() {}

void tintegrationall::cleanupTestCase() {}

void tintegrationall::test_milchkaffee() {}

QTEST_APPLESS_MAIN(tintegrationall)

#include "tst_tintegrationall.moc"
