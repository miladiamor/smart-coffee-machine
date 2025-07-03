#include <QtTest>

// add necessary includes here

class fuellstandsmessung : public QObject
{
    Q_OBJECT

public:
    fuellstandsmessung();
    ~fuellstandsmessung();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

fuellstandsmessung::fuellstandsmessung() {}

fuellstandsmessung::~fuellstandsmessung() {}

void fuellstandsmessung::initTestCase() {}

void fuellstandsmessung::cleanupTestCase() {}

void fuellstandsmessung::test_case1() {}

QTEST_APPLESS_MAIN(fuellstandsmessung)

#include "tst_fuellstandsmessung.moc"
