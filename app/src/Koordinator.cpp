#include "Koordinator.h"
#include <QDebug>

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
        qDebug() << "[Koordinator] Missing component(s)";
        return;
    }

    lastTouch = display->getLastTouch();
    qDebug() << "[Koordinator] Current State:" << static_cast<int>(zustand);
    qDebug() << "[Koordinator] Last Touch:" << lastTouch;

    switch (zustand) {
    case KoordinatorZustand::WARTEN:
        zeigeBild(":/images/selection.png");

        if (lastTouch != QPointF(0, 0)) {
            int width = 400;   // adjust as needed
            int height = 400;  // adjust as needed

            Ressourcen res; // Empty for now
            kaffeeprogramm = new Kaffeeprogramm(res);

            if (lastTouch.x() < width / 2 && lastTouch.y() < height / 2) {
                qDebug() << "[Koordinator] Selected: Milchkaffee";
                kaffeeprogramm->setKaffeemenge_g(15);
                kaffeeprogramm->setMilchmenge_ml(150);
                kaffeeprogramm->setWassermenge_ml(50);
                kaffeeprogramm->setWasserKochhitze_Cel(90);
                kaffeeprogramm->setMilchKochhitze_Cel(65);
            } else if (lastTouch.x() >= width / 2 && lastTouch.y() < height / 2) {
                qDebug() << "[Koordinator] Selected: KaffeeCrema";
                kaffeeprogramm->setKaffeemenge_g(18);
                kaffeeprogramm->setMilchmenge_ml(0);
                kaffeeprogramm->setWassermenge_ml(150);
                kaffeeprogramm->setWasserKochhitze_Cel(92);
                kaffeeprogramm->setMilchKochhitze_Cel(0);
            } else if (lastTouch.x() < width / 2 && lastTouch.y() >= height / 2) {
                qDebug() << "[Koordinator] Selected: LatteMacchiato";
                kaffeeprogramm->setKaffeemenge_g(12);
                kaffeeprogramm->setMilchmenge_ml(170);
                kaffeeprogramm->setWassermenge_ml(40);
                kaffeeprogramm->setWasserKochhitze_Cel(88);
                kaffeeprogramm->setMilchKochhitze_Cel(60);
            } else {
                qDebug() << "[Koordinator] Selected: Cappuccino";
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
                qDebug() << "[Koordinator] Sugar selected";
                mitZucker = true;
            } else {
                qDebug() << "[Koordinator] Sugar not selected";
                mitZucker = false;
            }
            kaffeeprogramm->setMitZucker(mitZucker);
            zustand = KoordinatorZustand::BEZAHLEN;
        }
        break;

    case KoordinatorZustand::BEZAHLEN:
        zeigeBild(":/images/brewing.png"); // placeholder for payment
        qDebug() << "[Koordinator] Payment placeholder step";

        if (zahlungseinheit->versucheZahlung(kaffeeprogramm->getProdukt())) {
            qDebug() << "[Koordinator] Payment successful";
            zustand = KoordinatorZustand::AUSFUEHREN;
        } else {
            qDebug() << "[Koordinator] Waiting for payment";
        }
        break;

    case KoordinatorZustand::AUSFUEHREN:
        zeigeBild(":/images/brewing.png");
        qDebug() << "[Koordinator] Starting coffee program";

        programmsteuerung->ausfuehren(kaffeeprogramm);
        zustand = KoordinatorZustand::WARTEN_AUF_FERTIG;
        break;

    case KoordinatorZustand::WARTEN_AUF_FERTIG:
        if (programmsteuerung->istFertig()) {
            qDebug() << "[Koordinator] Coffee program finished";
            zustand = KoordinatorZustand::FERTIG;
        }
        break;

    case KoordinatorZustand::FERTIG:
        zeigeBild(":/images/done.png");
        qDebug() << "[Koordinator] Returning to WARTEN";
        zustand = KoordinatorZustand::WARTEN;
        break;
    }
}
