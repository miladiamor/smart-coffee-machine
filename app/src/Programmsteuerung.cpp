#include "Programmsteuerung.h"
#include "Heizregler.h"
#include "bruehgruppe.h"
#include "Schaeumer.h"
//#include "Zuckerdispenser.h"
//#include "Fuellstandsmessung.h"
#include "Pumpesteuerung.h"
//#include "clock.h"
#include "kaffeeprogramm.h"


#include <QDebug>


Programmsteuerung::Programmsteuerung()
   :status(0),
    programm(nullptr),
    temperaturregler_wasser(nullptr),
    temperaturregler_milch(nullptr),
    zucker(nullptr),
    milchschaeumer(nullptr),
    bruehgruppe(nullptr),
    steuerung(nullptr),
    messung(nullptr),
    coffeeState(CoffeeState::IDLE)
    {}

Programmsteuerung::~Programmsteuerung(){}

    void Programmsteuerung::setPumpesteuerung(Pumpesteuerung* pump_steuerung){
        this->steuerung = pump_steuerung;
        connect(steuerung, &Pumpesteuerung::pumpingFinished, this, &Programmsteuerung::onPumpingFinished);
        connect(steuerung, &Pumpesteuerung::fehler, this, &Programmsteuerung::fehleraufgetreten);
    }

    void Programmsteuerung::setBruehgruppe(Bruehgruppe* gruppe){
        this->bruehgruppe = gruppe;
    }

    void Programmsteuerung::setWasserHeizer(Heizregler* heizer){
        this->temperaturregler_wasser = heizer;
    }

    void Programmsteuerung::setMilchHeizer(Heizregler* heizer){
        this->temperaturregler_milch = heizer;
    }
    void Programmsteuerung::setMilchschaeumer(Schaeumer* schaeumer){
        this->milchschaeumer = schaeumer;
    }

    void Programmsteuerung::ausfuehren(Kaffeeprogramm *programm){
        {
            if (!steuerung || !bruehgruppe || !temperaturregler_wasser || !temperaturregler_milch || !milchschaeumer) {

                return;
            }

            if (coffeeState != CoffeeState::IDLE) {

                return;
            }

            this->currentProgramm = programm;
            coffeeState = CoffeeState::HEIZEN;
            temperaturregler_wasser->temperaturRegeln(currentProgramm->getWasserKochhitze_Cel());
            temperaturregler_milch->temperaturRegeln(currentProgramm->getMilchKochhitze_Cel());
            QTimer::singleShot(1000, this, SLOT(nextStep()));
        }
    }

    void Programmsteuerung::nextStep(){

        switch (coffeeState) {
        case CoffeeState::HEIZEN:
            coffeeState = CoffeeState::FUELLEN;
            bruehgruppe->kaffeeFuellen();
        case CoffeeState::FUELLEN:
            coffeeState = CoffeeState::PUMPING_WATER;
            steuerung->startPumpingWater(currentProgramm->getWassermenge_ml());
            break;
        case CoffeeState::PUMPING_MILK:
            coffeeState = CoffeeState::SCHAEUMEN;
            milchschaeumer->aufschaeumenStarten();
            QTimer::singleShot(2000, this, SLOT(nextStep()));
            break;
        case CoffeeState::SCHAEUMEN:
            coffeeState = CoffeeState::PROGRAMM_ABGESCHLOSSEN;
            milchschaeumer->aufschaeumenStoppen();
            bruehgruppe->entleeren();
            coffeeState = CoffeeState::IDLE;
            break;
        default:
            break;
        }

    }

    void Programmsteuerung::onPumpingFinished(){
        if(coffeeState == CoffeeState::PUMPING_WATER){
            coffeeState = CoffeeState::PUMPING_MILK;
            steuerung->startPumpingMilk(currentProgramm->getMilchmenge_ml());
        } else if(coffeeState == CoffeeState::PUMPING_MILK){
            nextStep();
        }
    }

    void Programmsteuerung::fehleraufgetreten(const QString& message){

        coffeeState = CoffeeState::FEHLER;
    }
    /*void Programmsteuerung::ausfuehren(Kaffeeprogramm *programm) {

    status =  1;
    qDebug() << "Kaffeeprogramm gesetzt";

    // Durchlauferhitzer wasser und milch auf die richtige Temperatur bringen
     temperaturregler_milch->temperaturRegeln(programm->getMilchKochhitze_Cel());
    temperaturregler_wasser->temperaturRegeln(programm->getWasserKochhitze_Cel());
    QTimer::singleShot(5000, this, SLOT(nextStep()));

    bruehgruppe->kaffeeFuellen();
    QTimer::singleShot(6000, this, SLOT(nextStep()));


    // Wasser pumpen
    steuerung->mypumpe1(programm->getWassermenge_ml());
    QTimer::singleShot(1000, this, SLOT(nextStep()));

    //Milch pumpen
    steuerung->mypumpe2((programm->getMilchmenge_ml()));
    QTimer::singleShot(2000, this, SLOT(nextStep()));
    milchschaeumer->aufschaeumenStarten();
    QTimer::singleShot(1000, this, SLOT(nextStep()));
    milchschaeumer->aufschaeumenStoppen();
    QTimer::singleShot(500, this, SLOT(nextStep()));

    bruehgruppe->entleeren();*/

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


  //  status = 0;
  //  qDebug() << "Kaffeeprogramm abgeschlossen";
//}


