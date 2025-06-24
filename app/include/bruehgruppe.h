#ifndef BRUEHGRUPPE_H
#define BRUEHGRUPPE_H

#include <QObject>
#include <QTimer>
#include "ventil.h"
#include "klappe.h"
class Bruehgruppe;
#include "motorsteuerung.h"
#include "kaffeeprogramm.h"

enum BruehState {WARTEN, ENTLEEREN, STAMPFEN, KOCHEN, KAFFEEZUFUHR, ZURUECKSETZEN};
enum BruehEvent {ZUFUHRSTART, ZUFUHRABGESCHLOSSEN, MOTORABGESCHLOSSEN, KOCHENAUFGEHOERT};
class Bruehgruppe : public QObject
{
Q_OBJECT
public:
    Bruehgruppe(QObject *parent = nullptr);
    ~Bruehgruppe();

    void trigger(BruehEvent event);
    BruehState getState();
    void setKaffeeprogramm(Kaffeeprogramm *kaffeeprogramm);
    void setMotorsteuerung(Motorsteuerung *motorsteuerung);
    void setTropfstopfventil(Ventil *tropfstopfventil);
    void setWasserzufuhr(Ventil *wasserzufuhr);
    void setKaffeezufuhr(Ventil *kaffeeezufuhr);
    void setEntleerklappe(Klappe *entleerklappe);

private:
    BruehState state;
    Ventil *tropfstopfventil, *wasserzufuhr, *kaffeezufuhr;
    Klappe *entleerklappe;
    Motorsteuerung *motorsteuerung;
    Kaffeeprogramm *kaffeeprogramm;
};

#endif

