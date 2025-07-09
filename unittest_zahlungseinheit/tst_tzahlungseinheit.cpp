#include <QtTest>
#include <QObject>

#include "Zahlungseinheit.h"
#include "MuenzEingabeSensor.h"
#include "Muenzroehrenspeicher.h"
#include "MuenzAuswerfer.h"
#include "display.h"
// === GLOBALE FLAGS FÜR TEST-VERIFIKATION ===
int displayCalled = 0;
QString lastDisplayedText;

bool muenzeGueltigReturn = true;
float eingeworfeneMuenzeReturn = 1.0f;

bool fuegeMuenzeEinReturn = true;
bool geldAuswerfenCalled = false;
float geldAuswerfenAmount = 0.0f;

// === MOCK Display ===
Display::Display(QObject *parent) : QObject{parent} {}

Display::~Display() {}

void Display::displayText(QString text) {
    displayCalled++;
    lastDisplayedText = text;
}
void Display::acceptTouch(QPointF ) {
}

// === MOCK MuenzEingabeSensor ===
MuenzEingabeSensor::MuenzEingabeSensor() {}
bool MuenzEingabeSensor::getMuenzeGueltig() {
    return muenzeGueltigReturn;
}
float MuenzEingabeSensor::getEingeworfeneMuenze() {
    return eingeworfeneMuenzeReturn;
}
void MuenzEingabeSensor::setEingeworfeneMuenze(float) {
}


// === MOCK Muenzroehrenspeicher ===
Muenzroehrenspeicher::Muenzroehrenspeicher() {}

bool Muenzroehrenspeicher::fuegeMuenzeEin(float) {
    return fuegeMuenzeEinReturn;
}
void Muenzroehrenspeicher::geldAuswerfen(float betrag) {
    geldAuswerfenCalled = true;
    geldAuswerfenAmount = betrag;
}
void Muenzroehrenspeicher::muenzeAuswerfen(float) {}
void Muenzroehrenspeicher::tick() {}


// === MOCK MuenzAuswerfer ===
MuenzAuswerfer::MuenzAuswerfer() {}
void MuenzAuswerfer::auswerfenMuenze(Muenzroehre *) {}

// === Test Implementation ===
class tzahlungseinheit : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {}
    void cleanupTestCase() {}
    void init();
    void cleanup();
    void testStartPayment();
    void testOverpaymentReturnsChange();
    void testDisplayUpdatesCorrectly();

private:
    Zahlungseinheit* sut;          // System Under Test
    Display* mockDisplay;
    MuenzEingabeSensor* mockSensor;
    Muenzroehrenspeicher* mockSpeicher;
    MuenzAuswerfer* mockAuswerfer;
};
void tzahlungseinheit::init() {
    mockDisplay = new Display();
    mockSensor = new MuenzEingabeSensor();
    mockSpeicher = new Muenzroehrenspeicher();
    mockAuswerfer = new MuenzAuswerfer();

    sut = new Zahlungseinheit();
    sut->setDisplay(mockDisplay);
    sut->setMuenzAuswerfer();

}
void tzahlungseinheit::cleanup() {
    displayCalled = 0;
    lastDisplayedText = "";
    muenzeGueltigReturn = true;
    eingeworfeneMuenzeReturn = 1.0f;
    fuegeMuenzeEinReturn = true;
    geldAuswerfenCalled = false;
    geldAuswerfenAmount = 0.0f;
}
void tzahlungseinheit::testStartPayment() {

    QVERIFY(!sut->getZahlungErfolgreich());

    float preis = 1.5f;
    sut->versucheZahlung(preis);

    QVERIFY(!sut->getZahlungErfolgreich());

}
void tzahlungseinheit::testOverpaymentReturnsChange() {
    // Arrange
    sut->versucheZahlung(1.0f); // Start payment with 1.0€

    muenzeGueltigReturn = true;         // Simulate valid coin
    eingeworfeneMuenzeReturn = 2.0f;    // Insert 2.0€ coin
    fuegeMuenzeEinReturn = true;        // Coin accepted

    int prevDisplayCalled = displayCalled;

    //  Simulate payment system ready to process inserted coin
   sut->setTestZahlungAktiv(false);

    // Act
    sut->tick();

    // Assert
    QVERIFY(sut->getZahlungErfolgreich());             // Payment should complete
    QVERIFY(geldAuswerfenCalled);                      // Change should be returned
    QCOMPARE(geldAuswerfenAmount, 1.0f);               // Correct change returned
   QVERIFY(displayCalled == prevDisplayCalled + 1);
}

void tzahlungseinheit::testDisplayUpdatesCorrectly() {
    // Arrange
    sut->versucheZahlung(1.5f); // Start payment with 1.5€

    muenzeGueltigReturn = true;         // Simulate valid coin
    eingeworfeneMuenzeReturn = 1.0f;    // Insert 1.0€ coin
    fuegeMuenzeEinReturn = true;        // Coin accepted

    int prevDisplayCalled = displayCalled;

    // Simulate payment system ready to process inserted coin
    sut->setTestZahlungAktiv(false);

    // Act
    sut->tick();

    // Assert
    QVERIFY(displayCalled > prevDisplayCalled);                  // Display should be updated
    QCOMPARE(lastDisplayedText, QString("Zu bezahlen: 0.50 €")); // Correct remaining amount displayed
    QVERIFY(!sut->getZahlungErfolgreich());                     // Payment should not yet be complete
}



QTEST_APPLESS_MAIN(tzahlungseinheit)
#include "tst_tzahlungseinheit.moc"
