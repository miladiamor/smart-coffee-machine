#include "Programmsteuerung.h"
#include "Heizregler.h"
#include "bruehgruppe.h"
#include "Schaeumer.h"
#include "Zuckerdispenser.h"
#include "Fuellstandsmessung.h"
#include "Pumpsteuerung.h"



#include <QDebug>

Programmsteuerung::Programmsteuerung(){
    status = 0;
    programm = nullptr;
    temp_regler = nullptr;
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

    status =  1;
    qDebug() << "Kaffeeprogramm gesetzt";

    if (!ressourcenCheck()){
        qDebug() << "Nicht genuegend Ressourcen";
        return;
    }

    steuerung->pumpen(100);
    temp_regler->temperaturRegeln(92);
    bruehgruppe->kaffee_pressen(5);
    bruehgruppe->kaffeepulver_hinzufuegen(10);
    bruehgruppe->wasserzufuhr_oeffnen();
    milchschaeumer->aufschaeumenStarten();
    zucker->zuckerAuswerfen();
    bruehgruppe->wasserzufuhr_schliessen();
    milchschaeumer->aufschaeumenStoppen();
    temp_regler->regelnStoppen();

    status = 0;
    qDebug() << "Kaffeeprogramm abgeschlossen";
}

bool Programmsteuerung::ressourcenCheck(){
    ressourcen res = messung->getRessourcen();
    return res.wasser > 100 && res.kaffee > 10;
}
