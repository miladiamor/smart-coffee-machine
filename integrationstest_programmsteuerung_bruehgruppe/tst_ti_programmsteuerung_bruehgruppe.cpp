#include <QtTest>

// add necessary includes here
#include "bruehgruppe.h"
#include "programmsteuerung.h"


void Ventil::schliessen() {}

class ti_programmsteuerung_bruehgruppe : public QObject
{
    Q_OBJECT

public:
    ti_programmsteuerung_bruehgruppe();
    ~ti_programmsteuerung_bruehgruppe();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

ti_programmsteuerung_bruehgruppe::ti_programmsteuerung_bruehgruppe() {}

ti_programmsteuerung_bruehgruppe::~ti_programmsteuerung_bruehgruppe() {}

void ti_programmsteuerung_bruehgruppe::initTestCase() {}

void ti_programmsteuerung_bruehgruppe::cleanupTestCase() {}

void ti_programmsteuerung_bruehgruppe::test_case1() {}

QTEST_APPLESS_MAIN(ti_programmsteuerung_bruehgruppe)

#include "tst_ti_programmsteuerung_bruehgruppe.moc"
