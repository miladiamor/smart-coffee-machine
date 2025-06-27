#include <QtTest>
#include "display.h"
#include "koordinator.h"

// add necessary includes here


class tdisplay : public QObject
{
    Q_OBJECT

public:
    tdisplay();
    ~tdisplay();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

tdisplay::tdisplay() {}

tdisplay::~tdisplay() {}

void tdisplay::initTestCase() {}

void tdisplay::cleanupTestCase() {}

void tdisplay::test_case1() {}

QTEST_APPLESS_MAIN(tdisplay)

#include "tst_tdisplay.moc"
