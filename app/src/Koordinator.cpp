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
        display->displayScreen(QImage(pfad)); // mock
    }
}

void Koordinator::tick() {
    if (!display || !programmsteuerung || !zahlungseinheit || !fuellstandsmessung) {
        return;
    }

    lastTouch = display->getLastTouch(); // mock

    switch (zustand) {
    case KoordinatorZustand::WARTEN:
        zeigeBild(":/images/selection.png");

        if (lastTouch != QPointF(0, 0)) {
            int width = 400;
            int height = 400;

            Ressourcen res;
            kaffeeprogramm = new Kaffeeprogramm(res); // mock

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
            mitZucker = lastTouch.x() < width / 2;
            kaffeeprogramm->setMitZucker(mitZucker); // mock
            zustand = KoordinatorZustand::BEZAHLEN;
        }
        break;

    case KoordinatorZustand::BEZAHLEN:
        zeigeBild(":/images/brewing.png");

        if (zahlungseinheit->versucheZahlung(kaffeeprogramm->getProdukt())) { // mock
            zustand = KoordinatorZustand::AUSFUEHREN;
        }
        break;

    case KoordinatorZustand::AUSFUEHREN:
        zeigeBild(":/images/brewing.png");
        programmsteuerung->ausfuehren(kaffeeprogramm); // mock
        zustand = KoordinatorZustand::WARTEN_AUF_FERTIG;
        break;

    case KoordinatorZustand::WARTEN_AUF_FERTIG:
        if (programmsteuerung->istFertig()) { // mock
             zeigeBild(":/images/done.png");
            zustand = KoordinatorZustand::FERTIG;
        }
        break;

    case KoordinatorZustand::FERTIG:
        zeigeBild(":/images/done.png");
        zustand = KoordinatorZustand::WARTEN;
        break;
    }
}
