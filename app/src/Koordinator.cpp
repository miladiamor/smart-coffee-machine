#include "Koordinator.h"
#include "Produkt.h"
#include "Programmsteuerung.h"
#include "Zahlungseinheit.h"
#include "Kaffeeprogramm.h"
#include "display.h"
#include <QImage>

// Constructor
Koordinator::Koordinator()
    : zahlungseinheit(nullptr),
    programmsteuerung(nullptr),
    display(nullptr),
    zustand(KoordinatorZustand::WARTEN),
    mitZucker(false),
    lastTouch(-1, -1) // init invalid
{
    zeigeBild(":/selection.png");
}

// Helper: Show image
void Koordinator::zeigeBild(const QString& pfad) {
    if (display) {
        QImage bild(pfad);
        display->displayScreen(bild);
    }
}

// Setters
void Koordinator::setzeDisplay(Display* d) {
    display = d;
    zeigeBild(":/selection.png");
}

void Koordinator::setzeProgrammsteuerung(Programmsteuerung* p) {
    programmsteuerung = p;
}

void Koordinator::setzeZahlungseinheit(Zahlungseinheit* z) {
    zahlungseinheit = z;
}

// Getränkeauswahl
void Koordinator::waehleCappuccino() { /* same as before */ kaffeeprogramm.setKaffeemenge_g(9);
    kaffeeprogramm.setWassermenge_ml(30);
    kaffeeprogramm.setMilchmenge_ml(120);
    kaffeeprogramm.setWasserKochhitze_Cel(93);
    kaffeeprogramm.setMilchKochhitze_Cel(65);
    kaffeeprogramm.setMilchZuerst(true);
    zustand = KoordinatorZustand::ZUCKERWAHL;
    zeigeBild(":/sugar.png");
}

void Koordinator::waehleMilchkaffee() { /* same as before */
    kaffeeprogramm.setKaffeemenge_g(9);
    kaffeeprogramm.setWassermenge_ml(30);
    kaffeeprogramm.setMilchmenge_ml(150);
    kaffeeprogramm.setWasserKochhitze_Cel(92);
    kaffeeprogramm.setMilchKochhitze_Cel(70);
    kaffeeprogramm.setMilchZuerst(true);
    zustand = KoordinatorZustand::ZUCKERWAHL;
    zeigeBild(":/sugar.png");
}

void Koordinator::waehleKaffeeCrema() { /* same as before */
    kaffeeprogramm.setKaffeemenge_g(9);
    kaffeeprogramm.setWassermenge_ml(80);
    kaffeeprogramm.setMilchmenge_ml(0);
    kaffeeprogramm.setWasserKochhitze_Cel(95);
    kaffeeprogramm.setMilchKochhitze_Cel(0);
    kaffeeprogramm.setMilchZuerst(false);
    zustand = KoordinatorZustand::ZUCKERWAHL;
    zeigeBild(":/sugar.png");
}

void Koordinator::waehleLatteMacchiato() { /* same as before */
    kaffeeprogramm.setKaffeemenge_g(9);
    kaffeeprogramm.setWassermenge_ml(30);
    kaffeeprogramm.setMilchmenge_ml(200);
    kaffeeprogramm.setWasserKochhitze_Cel(92);
    kaffeeprogramm.setMilchKochhitze_Cel(60);
    kaffeeprogramm.setMilchZuerst(true);
    zustand = KoordinatorZustand::ZUCKERWAHL;
    zeigeBild(":/sugar.png");
}

// Zuckerwahl
void Koordinator::waehleZucker(bool mitZucker) {
    this->mitZucker = mitZucker;
    kaffeeprogramm.setMitZucker(mitZucker);
    zustand = KoordinatorZustand::BEZAHLEN;
}

// Kaufabwicklung
void Koordinator::fuehreKaufDurch() {
    if (!zahlungseinheit) return;

    Produkt* produkt = kaffeeprogramm.getProdukt();
    if (!produkt) return;

    bool bezahlt = zahlungseinheit->versucheZahlung(produkt);

    if (bezahlt) {
        zustand = KoordinatorZustand::AUSFUEHREN;
        zeigeBild(":/brewing.png");
        if (programmsteuerung) {
            programmsteuerung->ausfuehren(&kaffeeprogramm);
        }
    } else {
        zustand = KoordinatorZustand::WARTEN;
        zeigeBild(":/selection.png");
    }
}

// Tick function: replaces verarbeiteTouch and update
void Koordinator::tick() {
    if (programmsteuerung) {
        programmsteuerung->tick();
    }

    // Poll touch
    if (!display) return;
    QPointF touch = display->getLastTouch();

    if (touch != lastTouch) { // new touch detected
        lastTouch = touch;

        if (zustand == KoordinatorZustand::WARTEN) {
            if (touch.x() < 200 && touch.y() < 200) {
                waehleCappuccino();
            } else if (touch.x() > 200 && touch.y() < 200) {
                waehleMilchkaffee();
            } else if (touch.x() < 200 && touch.y() > 200) {
                waehleKaffeeCrema();
            } else if (touch.x() > 200 && touch.y() > 200) {
                waehleLatteMacchiato();
            }
        }
        else if (zustand == KoordinatorZustand::ZUCKERWAHL) {
            if (touch.x() < 200 && touch.y() < 200) {
                waehleZucker(true);
            } else if (touch.x() > 200 && touch.y() < 200) {
                waehleZucker(false);
            }
        }
        else if (zustand == KoordinatorZustand::BEZAHLEN) {
            if (touch.x() > 100 && touch.x() < 300 &&
                touch.y() > 300 && touch.y() < 400) {
                fuehreKaufDurch();
            }
        }
    }

    // Check if brewing finished
    if (zustand == KoordinatorZustand::AUSFUEHREN) {
        if (programmsteuerung && programmsteuerung->istFertig()) {
            zeigeBild(":/done.png");
            zustand = KoordinatorZustand::WARTEN;
            zeigeBild(":/selection.png");
        }
    }
}
