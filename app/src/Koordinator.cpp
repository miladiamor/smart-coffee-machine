#include "Koordinator.h"

Koordinator::Koordinator()
    : zahlungseinheit(nullptr),
    programmsteuerung(nullptr),
    zustand(KoordinatorZustand::WARTEN),
    mitZucker(false)
{
}

// Setup
void Koordinator::setzeZahlungseinheit(Zahlungseinheit* z) {
    zahlungseinheit = z;
}

void Koordinator::setzeProgrammsteuerung(Programmsteuerung* p) {
    programmsteuerung = p;
}

// Getränkeauswahl
void Koordinator::waehleCappuccino() {
    kaffeeprogramm.setKaffeemenge_g(9);
    kaffeeprogramm.setWassermenge_ml(30);
    kaffeeprogramm.setMilchmenge_ml(120);
    kaffeeprogramm.setWasserKochhitze_Cel(93);
    kaffeeprogramm.setMilchKochhitze_Cel(65);
    kaffeeprogramm.setMilchZuerst(true);
    zustand = KoordinatorZustand::ZUCKERWAHL;
}

void Koordinator::waehleMilchkaffee() {
    kaffeeprogramm.setKaffeemenge_g(9);
    kaffeeprogramm.setWassermenge_ml(30);
    kaffeeprogramm.setMilchmenge_ml(150);
    kaffeeprogramm.setWasserKochhitze_Cel(92);
    kaffeeprogramm.setMilchKochhitze_Cel(70);
    kaffeeprogramm.setMilchZuerst(true);
    zustand = KoordinatorZustand::ZUCKERWAHL;
}

void Koordinator::waehleKaffeeCrema() {
    kaffeeprogramm.setKaffeemenge_g(9);
    kaffeeprogramm.setWassermenge_ml(80);
    kaffeeprogramm.setMilchmenge_ml(0);
    kaffeeprogramm.setWasserKochhitze_Cel(95);
    kaffeeprogramm.setMilchKochhitze_Cel(0);
    kaffeeprogramm.setMilchZuerst(false);
    zustand = KoordinatorZustand::ZUCKERWAHL;
}

void Koordinator::waehleLatteMacchiato() {
    kaffeeprogramm.setKaffeemenge_g(9);
    kaffeeprogramm.setWassermenge_ml(30);
    kaffeeprogramm.setMilchmenge_ml(200);
    kaffeeprogramm.setWasserKochhitze_Cel(92);
    kaffeeprogramm.setMilchKochhitze_Cel(60);
    kaffeeprogramm.setMilchZuerst(true);
    zustand = KoordinatorZustand::ZUCKERWAHL;
}

// Zuckerwahl
void Koordinator::waehleZucker(bool mitZucker) {
    this->mitZucker = mitZucker;
    kaffeeprogramm.setMitZucker(mitZucker);
    zustand = KoordinatorZustand::BEZAHLEN;
}

// Kauf und Ausführung
void Koordinator::kaufeGetraenk() {
    if (!zahlungseinheit) return;

    Produkt* produkt = kaffeeprogramm.getProdukt();
    if (!produkt) return;

    bool bezahlt = zahlungseinheit->versucheZahlung(produkt);
    if (bezahlt) {
        zustand = KoordinatorZustand::AUSFUEHREN;
        if (programmsteuerung) {
            programmsteuerung->ausfuehren(&kaffeeprogramm);
        }
    } else {
        zustand = KoordinatorZustand::WARTEN;
    }
}
