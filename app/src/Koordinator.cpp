#include "Koordinator.h"

Koordinator::Koordinator() {}

void Koordinator::setzeDisplay(Display* d) {
    display = d;
}

void Koordinator::setzeProgrammsteuerung(Programmsteuerung* p) {
    programmsteuerung = p;
}

void Koordinator::setzeZahlungseinheit(Zahlungseinheit* z) {
    zahlungseinheit = z;
}

void Koordinator::setzeFuellstandsmessung(Fuellstandsmessung* f) {
    fuellstandsmessung = f;
}

void Koordinator::zeigeBild(const QString& pfad) {
    if (display) {
        display->displayScreen(QImage(pfad));
    }
}

void Koordinator::tick() {
    if (!display || !programmsteuerung || !zahlungseinheit || !fuellstandsmessung) {
        return;
    }

    lastTouch = display->getLastTouch();

    switch (zustand) {
    case KoordinatorZustand::WARTEN:
        zeigeBild(":/images/selection.png");

        if (lastTouch != QPointF(0, 0)) {
            int width = 400;   // adjust as needed
            int height = 400;  // adjust as needed

            Ressourcen res;
            kaffeeprogramm = new Kaffeeprogramm(res);

            if (lastTouch.x() < width / 2 && lastTouch.y() < height / 2) {
                kaffeeprogramm->setKaffeemenge_g(15);
                kaffeeprogramm->setMilchmenge_ml(150);
                kaffeeprogramm->setWassermenge_ml(50);
                kaffeeprogramm->setWasserKochhitze_Cel(90);
                kaffeeprogramm->setMilchKochhitze_Cel(65);
            } else if (lastTouch.x() >= width / 2 && lastTouch.y() < height / 2) {
                kaffeeprogramm->setKaffeemenge_g(18);
                kaffeeprogramm->setMilchmenge_ml(0);
                kaffeeprogramm->setWassermenge_ml(150);
                kaffeeprogramm->setWasserKochhitze_Cel(92);
                kaffeeprogramm->setMilchKochhitze_Cel(0);
            } else if (lastTouch.x() < width / 2 && lastTouch.y() >= height / 2) {
                kaffeeprogramm->setKaffeemenge_g(12);
                kaffeeprogramm->setMilchmenge_ml(170);
                kaffeeprogramm->setWassermenge_ml(40);
                kaffeeprogramm->setWasserKochhitze_Cel(88);
                kaffeeprogramm->setMilchKochhitze_Cel(60);
            } else {
                kaffeeprogramm->setKaffeemenge_g(14);
                kaffeeprogramm->setMilchmenge_ml(120);
                kaffeeprogramm->setWassermenge_ml(60);
                kaffeeprogramm->setWasserKochhitze_Cel(90);
                kaffeeprogramm->setMilchKochhitze_Cel(65);
            }

            zustand = KoordinatorZustand::ZUCKERWAHL;
        }
        break;

    case KoordinatorZustand::ZUCKERWAHL:
        zeigeBild(":/images/sugar.png");

        if (lastTouch != QPointF(0, 0)) {
            int width = 400;
            if (lastTouch.x() < width / 2) {
                mitZucker = true;
            } else {
                mitZucker = false;
            }
            kaffeeprogramm->setMitZucker(mitZucker);
            zustand = KoordinatorZustand::BEZAHLEN;
        }
        break;

    case KoordinatorZustand::BEZAHLEN:
        zeigeBild(":/images/brewing.png"); //new foto muss erstellt

        if (zahlungseinheit->versucheZahlung(kaffeeprogramm->getProdukt())) {
            zustand = KoordinatorZustand::AUSFUEHREN;
        }
        break;

    case KoordinatorZustand::AUSFUEHREN:
        zeigeBild(":/images/brewing.png");
        programmsteuerung->ausfuehren(kaffeeprogramm);
        zustand = KoordinatorZustand::WARTEN_AUF_FERTIG;
        break;

    case KoordinatorZustand::WARTEN_AUF_FERTIG:
        if (programmsteuerung->istFertig()) {
            zustand = KoordinatorZustand::FERTIG;
        }
        break;

    case KoordinatorZustand::FERTIG:
        zeigeBild(":/images/done.png");
        zustand = KoordinatorZustand::WARTEN;
        break;
    }
}
