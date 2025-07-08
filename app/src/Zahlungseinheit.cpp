#include "Zahlungseinheit.h"

// Konstruktor ohne Parameter fuer Unittests
Zahlungseinheit::Zahlungseinheit() {
    roehren = nullptr;
    eingabe = nullptr;
    auswerfer = nullptr;
    gesamterEinwurf = 0.0f;
    zahlungAktiv = false;
}

// Konstruktor mit Abhaengigkeiten
Zahlungseinheit::Zahlungseinheit(Muenzroehrenspeicher* roehren,
                                 MuenzEingabeSensor* eingabe,
                                 MuenzAuswerfer* auswerfer)
    : zahlungAktiv(false), gesamterEinwurf(0.0f),
    roehren(roehren),
    eingabe(eingabe), auswerfer(auswerfer) {}

// Initialisiert die Zahlung fuer ein Produkt
//bool Zahlungseinheit::versucheZahlung() {


//    return true;
//}

// Fuehrt einen Tick aus: verarbeitet eine Muenze
void Zahlungseinheit::tick() {
   // if (!zahlungAktiv || state != ZAHLUNG_LAEUFT)
     //   return;
}

// Bricht den Zahlungsvorgang ab und gibt Geld zurueck
void Zahlungseinheit::zahlungAbbrechen() {
    if (zahlungAktiv) {

    }
}
