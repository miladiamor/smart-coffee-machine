#include "Programmsteuerung.h"
#include "Heizregler.h"
#include "bruehgruppe.h"
#include "Schaeumer.h"
#include "Zuckerdispenser.h"
#include "Fuellstandsmessung.h"
#include "Pumpesteuerung.h"



#include <QDebug>
#include <memory>

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

void Programmsteuerung::ausfuehren(int dummyProgrammID) {
    Q_UNUSED(dummyProgrammID);

    if(!programm){
        qDebug() << "Kein Kaffeeprogramm gesetzt";
        return;
    }

    if (!temperaturregler_wasser || temperaturregler_milch || steuerung || !bruehgruppe || milchschaeumer || !zucker || messung) {
        qDebug() <<"Ein oder mehrere Komponenten sind nicht intialisiert";
        return;
    }

    status =  1;
    qDebug() << "Kaffeeprogramm gesetzt";

    // Durchlauferhitzer wasser und milch auf die richtige Temperatur bringen
    temperaturregler_milch->temperaturRegeln(programm->getMilchKochhitze());
    temperaturregler_wasser->temperaturRegeln(92);
    // Kaffee in brühgruppe schieben
    bruehgruppe->kaffeepulver_hinzufuegen(10);
    bruehgruppe->kaffee_pressen(5);

    // Kaffee vorbereiten
    bruehgruppe->kaffeepulver_hinzufuegen(10);
    bruehgruppe->kaffee_pressen(5);
    // Milch pumpen
     milchschaeumer->aufschaeumenStarten();
    //  Milch fertig
     milchschaeumer->aufschaeumenStoppen();
    // Wasserzufuhrventil in Brühgruppe öffnen
    bruehgruppe->wasserzufuhr_oeffnen();
    //Wasser pumpen
    steuerung->pumpen(100);
    // zucker ausgeben
    zucker->zuckerAuswerfen();
    // Wasserzufuhr schließen
    bruehgruppe->wasserzufuhr_schliessen();
    //tropfstopfventil schließen

    // Brühgruppe entleeren
    bruehgruppe->entleeren();
    // einmal mit Wasser spülen (reinigen)
    bruehgruppe->wasserzufuhr_oeffnen();
    steuerung->pumpen(50);
    bruehgruppe->wasserzufuhr_schliessen();
    bruehgruppe->entleeren();
    // Ventille schließen

    // Heizregler

   /* steuerung->pumpen(100);
    bruehgruppe->kaffee_pressen(5);
    bruehgruppe->kaffeepulver_hinzufuegen(10);
    bruehgruppe->wasserzufuhr_oeffnen();
    milchschaeumer->aufschaeumenStarten();
    zucker->zuckerAuswerfen();
    bruehgruppe->wasserzufuhr_schliessen();
    milchschaeumer->aufschaeumenStoppen();
    temperaturregler_milch->regelnStoppen();
    temperaturregler_wasser->regelnStoppen();
*/
    status = 0;
    qDebug() << "Kaffeeprogramm abgeschlossen";
}

/*bool Programmsteuerung::ressourcenCheck(){
    std::shared_ptr<Ressourcen> res = messung ->getRessourcen();
    return res->getWassermenge_ml() > 100 && res->getKaffeemenge_g() > 10;
    //ressourcen res = messung->getRessourcen();
    //return res.wasser > 100 && res.kaffee > 10;
}
*/
