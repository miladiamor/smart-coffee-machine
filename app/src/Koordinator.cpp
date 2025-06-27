#include "Koordinator.h"
#include "Produkt.h"
#include "Programmsteuerung.h"
#include "Zahlungseinheit.h"
#include "Kaffeeprogramm.h"
#include "display.h"
#include <QPointF>

// Konstruktor
Koordinator::Koordinator()
    : zahlungseinheit(nullptr),
    programmsteuerung(nullptr),
    display(nullptr),
    zustand(KoordinatorZustand::WARTEN),
    mitZucker(false)
{
}

// Setze Display
void Koordinator::setzeDisplay(Display* d) {
    this->display = d;
}

// Setze Programmsteuerung
void Koordinator::setzeProgrammsteuerung(Programmsteuerung* p) {
    programmsteuerung = p;
}

// Setze Zahlungseinheit
void Koordinator::setzeZahlungseinheit(Zahlungseinheit* z) {
    zahlungseinheit = z;
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

// Kaufabwicklung und Ausführung
void Koordinator::fuehreKaufDurch() {
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

// Touch-Verarbeitung
void Koordinator::verarbeiteTouch(const QPointF& position) {
    if (zustand == KoordinatorZustand::WARTEN) {
        // Beispielhafte Bereiche prüfen (Dummy-Werte, anpassen an dein Layout)
        if (position.x() < 200 && position.y() < 200) {
            waehleCappuccino();
        } else if (position.x() > 200 && position.y() < 200) {
            waehleMilchkaffee();
        } else if (position.x() < 200 && position.y() > 200) {
            waehleKaffeeCrema();
        } else if (position.x() > 200 && position.y() > 200) {
            waehleLatteMacchiato();
        }
    }
    else if (zustand == KoordinatorZustand::ZUCKERWAHL) {
        // Example touch zones for sugar yes/no buttons:
        if (position.x() < 200 && position.y() < 200) {
            waehleZucker(true); // User wants sugar
        } else if (position.x() > 200 && position.y() < 200) {
            waehleZucker(false); // User does not want sugar
        }
    }
    else if (zustand == KoordinatorZustand::BEZAHLEN) {
        // Example touch zone for "Bezahlen" button:
        if (position.x() > 100 && position.x() < 300 &&
            position.y() > 300 && position.y() < 400) {
            fuehreKaufDurch();
        }
    }
}
