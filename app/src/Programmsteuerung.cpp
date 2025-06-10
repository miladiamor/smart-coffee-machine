#include "Programmsteuerung.h"
#include "Heizregler.h"
#include "bruehgruppe.h"
#include "Schaeumer.h"
#include "Zuckerdispenser.h"
//#include "Fuellstandsmessung.h"
#include "Pumpesteuerung.h"
//#include "clock.h"
#include "kaffeeprogramm.h"


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
     temperaturregler_milch->temperaturRegeln(programm->getMilchKochhitze_Cel());
    temperaturregler_wasser->temperaturRegeln(programm->getWasserKochhitze_Cel());
    QTimer::singleShot(5000, this, SLOT(nextStep()));

    bruehgruppe->kaffeeFuellen();
    /*
    Hier Wasser und Milch pumpen bitte. Die Brühgruppe kümmert sich jetzt um die Ventile das Füellen und das Entleeren!
    */
    bruehgruppe->entleeren();

    /*
     QTimer::singleShot(5000, this, SLOT(nextStep()));

    // Kaffee vorbereiten
     bruehgruppe->kaffeepulver_hinzufuegen(programm->getKaffeemenge_g());
     QTimer::singleShot(3000, this, SLOT(nextStep()));
     bruehgruppe->kaffee_pressen(programm->getstampfHoehe_mm());
     QTimer::singleShot(7000, this, SLOT(nextStep()));

    // Milch pumpen
     milchschaeumer->aufschaeumenStarten();
     QTimer::singleShot(15000, this, SLOT(nextStep()));

    //  Milch fertig
     milchschaeumer->aufschaeumenStoppen();

    // Wasserzufuhrventil in Brühgruppe öffnen
     bruehgruppe->wasserzufuhr_oeffnen();
     QTimer::singleShot(2000, this, SLOT(nextStep()));

    //Wasser pumpen
     steuerung->mypumpe(50);
     QTimer::singleShot(1000, this, SLOT(nextStep()));

    // zucker ausgeben
     zucker->zuckerAuswerfen();
     QTimer::singleShot(5000, this, SLOT(nextStep()));

    // Wasserzufuhr schließen
     bruehgruppe->wasserzufuhr_schliessen();

    //tropfstopfventil offnen
     bruehgruppe->tropfstopfventilOeffnen();
     QTimer::singleShot(3000, this, SLOT(nextStep()));

    //tropfstopfventil schließen
     bruehgruppe->tropfstopfventilSchließen();

    // Brühgruppe entleeren
     bruehgruppe->entleeren();
     QTimer::singleShot(5000, this, SLOT(nextStep()));

    // einmal mit Wasser spülen (reinigen)
     bruehgruppe->wasserzufuhr_oeffnen();
     steuerung->mypumpe(50);
     QTimer::singleShot(1000, this, SLOT(nextStep()));
     bruehgruppe->wasserzufuhr_schliessen();
     bruehgruppe->entleeren();
    */


    status = 0;
    qDebug() << "Kaffeeprogramm abgeschlossen";
}


