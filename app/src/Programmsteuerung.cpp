#include "Programmsteuerung.h"
#include "Heizregler.h"
#include "bruehgruppe.h"
#include "Schaeumer.h"
#include "Zuckerdispenser.h"
#include "Fuellstandsmessung.h"
#include "Pumpesteuerung.h"
#include "clock.h"


#include <QDebug>


Programmsteuerung::Programmsteuerung(){
    status = 0;
    programm = nullptr;
    temperaturregler_wasser = nullptr;
    temperaturregler_milch = nullptr;
    zucker = nullptr;
    milchschaeumer = nullptr;
    bruehgruppe = nullptr;
    steuerung = nullptr;
    messung = nullptr;
}

void Programmsteuerung::ausfuehren(Kaffeeprogramm *programm) {

    status =  1;
    qDebug() << "Kaffeeprogramm gesetzt";

    // Durchlauferhitzer wasser und milch auf die richtige Temperatur bringen
     temperaturregler_milch->temperaturRegeln(programm->getMilchKochhitze_cel());
     temperaturregler_wasser->temperaturRegeln(programm->getWassermenge_ml);
     QThread::msleep(1000);

    // Kaffee vorbereiten
     bruehgruppe->kaffeepulver_hinzufuegen(programm->getKaffeemenge_g);
     QThread::msleep(300);
     bruehgruppe->kaffee_pressen(programm->getstampfHoehe_mm);
     QThread::msleep(500);

    // Milch pumpen
     milchschaeumer->aufschaeumenStarten();
     QThread::msleep(1500);

    //  Milch fertig
     milchschaeumer->aufschaeumenStoppen();

    // Wasserzufuhrventil in Brühgruppe öffnen
     bruehgruppe->wasserzufuhr_oeffnen();
     QThread::msleep(200);

    //Wasser pumpen
     steuerung->pumpen(50);
     QThread::msleep(1000);

    // zucker ausgeben
     zucker->zuckerAuswerfen();
     QThread::msleep(500);

    // Wasserzufuhr schließen
     bruehgruppe->wasserzufuhr_schliessen();

    //tropfstopfventil offnen
     bruehgruppe->tropfstopfventilOeffnen();
     QThread::msleep(300);

    //tropfstopfventil schließen
     bruehgruppe->tropfstopfventilSchließen();

    // Brühgruppe entleeren
     bruehgruppe->entleeren();
     QThread::msleep(500);

    // einmal mit Wasser spülen (reinigen)
     bruehgruppe->wasserzufuhr_oeffnen();
     steuerung->pumpen(50);
     QThread::msleep(1000);
     bruehgruppe->wasserzufuhr_schliessen();
     bruehgruppe->entleeren();



    status = 0;
    qDebug() << "Kaffeeprogramm abgeschlossen";
}


