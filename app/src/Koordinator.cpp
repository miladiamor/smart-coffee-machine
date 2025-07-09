#include "Koordinator.h"
#include <QDebug>

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
    QImage img;
    img.load(pfad);
    display->displayScreen(img); // mock
}

void Koordinator::kaffeeprogrammEinstellen(float km_g, float mm_g, float wm_g, float wkh_cel, float mkh_cel, float sh_mm){
    kaffeeprogramm->setKaffeemenge_g(km_g);
    kaffeeprogramm->setMilchmenge_ml(mm_g);
    kaffeeprogramm->setWassermenge_ml(wm_g);
    kaffeeprogramm->setWasserKochhitze_Cel(wkh_cel);
    kaffeeprogramm->setMilchKochhitze_Cel(mkh_cel);
    kaffeeprogramm->setStampfhoehe_mm(sh_mm);
}

Kaffeeprogramm *Koordinator::getKaffeeprogramm() {
    return this->kaffeeprogramm;
}

void Koordinator::tick() {
    lastTouch = display->getLastTouch(); // mock
    switch (zustand) {
    case KoordinatorZustand::WARTEN:
        zeigeBild(":/selection.png");

        if (lastTouch != QPointF(0, 0)) {
            qDebug() << lastTouch.x() << ", " << lastTouch.y();
            int width = 300;
            int height = 300;

            Ressourcen res;
            kaffeeprogramm = new Kaffeeprogramm(res);

            if ((lastTouch.x() < width / 2) && (lastTouch.y() < height / 2)) {
                qDebug() << "kaffee ausgewählt";
                kaffeeprogrammEinstellen(15, 150, 50, 90, 65, 7);
            } else if ((lastTouch.x() >= width / 2) && (lastTouch.y() < height / 2)) {
                kaffeeprogrammEinstellen(18, 0, 150, 92, 0, 6);
            } else if ((lastTouch.x() < width / 2) && (lastTouch.y() >= height / 2)) {
                kaffeeprogrammEinstellen(12, 170, 40, 88, 60, 7);
            } else {
                kaffeeprogrammEinstellen(14, 120, 60, 90, 65, 6);
            }

            fuellstandsmessung->updateRessourcen();

            bool genugWasser = fuellstandsmessung->hatGenug(
                fuellstandsmessung->getWasserTank(),
                kaffeeprogramm->getWassermenge_ml(),
                1.0f);

            bool genugMilch = fuellstandsmessung->hatGenug(
                fuellstandsmessung->getMilchTank(),
                kaffeeprogramm->getMilchmenge_ml(),
                1.0f);

            bool genugKaffee = fuellstandsmessung->hatGenug(
                fuellstandsmessung->getKaffeeTank(),
                kaffeeprogramm->getKaffeemenge_g(),
                1.0f);

            qDebug() << "genug?";
            if (genugWasser && genugMilch && genugKaffee) {
                qDebug() << "KOOR.: ZUCKERWAHL";
                zustand = KoordinatorZustand::ZUCKERWAHL;
            } else {
                zeigeBild(":/not_enough.png");
                delete kaffeeprogramm;
                kaffeeprogramm = nullptr;
                zustand = KoordinatorZustand::WARTEN;
            }
        }
        break;


    case KoordinatorZustand::ZUCKERWAHL: {
        zeigeBild(":/sugar.png");

        if (lastTouch != QPointF(0, 0)) {
            qDebug() << lastTouch.x() << ", " << lastTouch.y();
            int width = 300;
            mitZucker = lastTouch.x() < width / 2;//casimir fragen
            kaffeeprogramm->setMitZucker(mitZucker);

            if (mitZucker) {
                bool genugZucker = fuellstandsmessung->hatGenug(
                    fuellstandsmessung->getZuckerTank(),
                    5,
                    1.0
                    );

                if (!genugZucker) {
                    zeigeBild(":/not_enough.png");
                    delete kaffeeprogramm;
                    kaffeeprogramm = nullptr;
                    zustand = KoordinatorZustand::WARTEN;
                    break;
                }
            }
            zahlungseinheit->versucheZahlung(5.0f);
            qDebug() << "KOOR.: Zahlung";
            zustand = KoordinatorZustand::BEZAHLEN;
        }
        break;
    }

    case KoordinatorZustand::BEZAHLEN: {
        if (zahlungseinheit->getZahlungErfolgreich()) { // mock
            zustand = KoordinatorZustand::AUSFUEHREN;
            qDebug() << "KOOR.: AUSFUEHREN";
        }
        break;
    }



    case KoordinatorZustand::AUSFUEHREN:
        zeigeBild(":/brewing.png");
        programmsteuerung->ausfuehren(kaffeeprogramm); // mock
        zustand = KoordinatorZustand::WARTEN_AUF_FERTIG;
        qDebug() << "KOOR.: WARTEN_AUF_FERTIG";
        break;

    case KoordinatorZustand::WARTEN_AUF_FERTIG:
        if (programmsteuerung->istFertig()) { // mock
             zeigeBild(":/done.png");
            zustand = KoordinatorZustand::FERTIG;
            qDebug() << "KOOR.: FERTIG";
        }
        break;

    case KoordinatorZustand::FERTIG:
        zustand = KoordinatorZustand::WARTEN;
        delete kaffeeprogramm;
        kaffeeprogramm = nullptr;
        qDebug() << "KOOR.: wARTEN";
        break;
    }
}
