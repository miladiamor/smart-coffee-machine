#ifndef BRUEHGRUPPE_H
#define BRUEHGRUPPE_H

#include <QObject>
#include <QTimer>
#include "ventil.h"
#include "klappe.h"
#include "kolbenmotor.h"
#include "inkrementalencoder.h"

class Bruehgruppe : public QObject
{
    Q_OBJECT
    public:
        Bruehgruppe();
        ~Bruehgruppe();
        void kaffee_pressen(int stampfHoehe_mm);
        void entleeren();
        void wasserzufuhr_oeffnen();
        void wasserzufuhr_schliessen();
        void kaffeepulver_hinzufuegen(int menge_g);
        bool getEntleerklappeOffen();
    private:
        QTimer sleeper;
        Ventil *tropfstopfventil, *wasserzufuhr, *kaffeezufuhr;
        Klappe *entleerklappe;
        Kolbenmotor *stampfer;
        Inkrementalencoder *inkrementalencoder;
};

#endif

