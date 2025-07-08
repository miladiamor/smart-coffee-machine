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
<<<<<<< HEAD
   // if (!zahlungAktiv || state != ZAHLUNG_LAEUFT)
     //   return;
=======
    if (!zahlungAktiv)
        return;
>>>>>>> 30046f7b3500397a1067f60dce93629d17faed4f

    float muenzwert = eingabe->getEingeworfeneMuenze();
    if (muenzwert <= 0.0f)
        return;

    if (!roehren->fuegeMuenzeEin(muenzwert)) {
        auswerfer->auswerfenMuenze(muenzwert);
        return;
    }

    gesamterEinwurf += muenzwert;

    if (gesamterEinwurf >= preis) {
        float rueckgeld = gesamterEinwurf - preis;
        if (rueckgeld > 0.0f) {

        }

        zahlungAktiv = false;
    }
}

// Bricht den Zahlungsvorgang ab und gibt Geld zurueck
void Zahlungseinheit::zahlungAbbrechen() {
    if (zahlungAktiv) {

    }
}
