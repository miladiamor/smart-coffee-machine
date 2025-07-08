#pragma once

#include <QPointF>
#include <QString>
#include <QImage>
#include <QObject>

#include "Kaffeeprogramm.h"
#include "Programmsteuerung.h"
#include "Zahlungseinheit.h"
#include "Fuellstandsmessung.h"
#include "Display.h"

enum class KoordinatorZustand {
    WARTEN,
    ZUCKERWAHL,
    BEZAHLEN,
    AUSFUEHREN,
    WARTEN_AUF_FERTIG,
    FERTIG
};

class Koordinator : public QObject
{
    Q_OBJECT
private:
    Kaffeeprogramm* kaffeeprogramm = nullptr;
    Programmsteuerung* programmsteuerung = nullptr;
    Zahlungseinheit* zahlungseinheit = nullptr;
    Fuellstandsmessung* fuellstandsmessung = nullptr;
    Display* display = nullptr;

    KoordinatorZustand zustand = KoordinatorZustand::WARTEN;
    bool mitZucker = false;
    QPointF lastTouch;

    void zeigeBild(const QString& pfad);
    void kaffeeprogrammEinstellen(float km_g, float mm_g, float wm_g, float wkh_cel, float mkh_cel, float sh_mm);
public:
    Koordinator(QObject *parent = nullptr)  : QObject{parent} {}

    void setzeDisplay(Display* d);
    void setzeProgrammsteuerung(Programmsteuerung* p);
    void setzeZahlungseinheit(Zahlungseinheit* z);
    void setzeFuellstandsmessung(Fuellstandsmessung* f);

    Kaffeeprogramm *getKaffeeprogramm();

    KoordinatorZustand getCurrentState() const {
        return zustand;
    }

public slots:
    void tick();
};
