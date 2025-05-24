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
        void kaffee_pressen(int stampfHoehe_mm);
        void entleeren();
        void tropfstopfventil_schliessen();
        void tropfstopfventil_oeffnen();
        void wasserzufuhr_oeffnen();
        void wasserzufuhr_schliessen();
        void kaffeepulver_hinzufuegen(int menge_g);

        int get_status();
    private:
        int status;
        QTimer sleeper;
        Ventil *tropfstopfventil, *wasserzufuhr, *kaffeezufuhr;
        Klappe *entleerklappe;
        Kolbenmotor *stampfer;
        Inkrementalencoder *inkrementalencoder;
};

#endif

