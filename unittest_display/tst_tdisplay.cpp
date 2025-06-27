#include <QObject>
#include <QtTest>
#include <QPointF>

#include "display.h"


class tdisplay : public QObject
{
    Q_OBJECT

private:
    QSignalSpy * spy;
    Display * sut;

public:
    tdisplay();
    ~tdisplay();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
    void testGetLastTouch();
    void testDisplayImage();
};

tdisplay::tdisplay() {}

tdisplay::~tdisplay() {}

void tdisplay::initTestCase() {}

void tdisplay::cleanupTestCase() {}

void tdisplay::init() {
    sut = new Display();
}

void tdisplay::cleanup() {
    delete sut;
}

void tdisplay::testGetLastTouch(){
    QPointF pt(34.5, 11.2);

    sut->acceptTouch(pt);

    QCOMPARE(pt, sut->getLastTouch());
}

void tdisplay::testDisplayImage(){
    spy = new QSignalSpy(sut, &Display::updateDisplay);
    QImage testImg = QImage("apple.png");

    sut->displayScreen(testImg);
    QCOMPARE(spy->count(), 1);

    QVariant arg = spy->takeFirst();
    QImage emitted = qvariant_cast<QImage>(arg);
    QCOMPARE(emitted, testImg);

    delete spy;
}

QTEST_APPLESS_MAIN(tdisplay)

#include "tst_tdisplay.moc"
