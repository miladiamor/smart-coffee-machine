#include "Programmsteuerung.h"
#include "Heizregler.h"
#include "bruehgruppe.h"
#include "Schaeumer.h"
#include "kaffeeprogramm.h"
#include "Pumpe.h"
#include "Zuckerdispenser.h"

#include <QDebug>

Programmsteuerung::Programmsteuerung()
   :busy(false),
    tickCounter(0),
    currentProgramm(nullptr),
    temperaturregler_wasser(nullptr),
    temperaturregler_milch(nullptr),
    zucker(nullptr),
    milchschaeumer(nullptr),
    bruehgruppe(nullptr),
    wasserpumpe(nullptr),
    milchpumpe(nullptr),
    coffeeState(CoffeeState::IDLE)
    {}

Programmsteuerung::~Programmsteuerung(){}

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
    void Programmsteuerung::setWasserpumpe(Pumpe* pumpe){
        this->wasserpumpe = pumpe;
    }
    void Programmsteuerung::setMilchpumpe(Pumpe* pumpe){
        this->milchpumpe = pumpe;
    }
    void Programmsteuerung::setZuckerdispenser(Zuckerdispenser* dispenser){
        this->zucker = dispenser;
    }

    void Programmsteuerung::ausfuehren(Kaffeeprogramm *programm){
        this->currentProgramm = programm;
        bruehgruppe->setKaffeeprogramm(programm);
        busy = true;
     }


    Programmsteuerung::CoffeeState Programmsteuerung::getCurrentState() const{
        return this->coffeeState;
    }

    void Programmsteuerung::setCurrentState(CoffeeState state){
        this->coffeeState = state;
    }

    bool Programmsteuerung::isBusy() const{
        return this->busy;
    }

    bool Programmsteuerung::istFertig() const {
        return !busy;

    }

    Kaffeeprogramm *Programmsteuerung::getKaffeeprogramm() {
        return this->currentProgramm;
    }

    void Programmsteuerung::tick(){
        if (!busy){
           return;
        }

        switch (coffeeState) {
        case CoffeeState::IDLE:
            if (busy == true) {
                temperaturregler_wasser->temperaturRegeln(currentProgramm->getWasserKochhitze_Cel());// Wassererhitzer starten
                temperaturregler_milch->temperaturRegeln(currentProgramm->getMilchKochhitze_Cel());// Millcherhitzer starten
                coffeeState = CoffeeState::HEIZEN;
            }
            qDebug() << "PS: IDLE";
            break;

        case CoffeeState::HEIZEN:
            if (temperaturregler_wasser->istTemperaturErreicht() && temperaturregler_milch->istTemperaturErreicht()){
                bruehgruppe->trigger(ZUFUHRSTART);
                coffeeState = CoffeeState::KAFFEE_ZUFUHR;
                tickCounter = 0;
            }
            qDebug() << "PS: HEIZEN";
            break;

        case CoffeeState::KAFFEE_ZUFUHR:
            if (tickCounter >= currentProgramm->getKaffeemenge_g()/0.3) {
                bruehgruppe->trigger(ZUFUHRABGESCHLOSSEN);
                coffeeState = CoffeeState::WARTENAUFBRUEHGRUPPE;
            }
            qDebug() << "PS: KAFFEEZUFUHR";
            break;

        case CoffeeState::WARTENAUFBRUEHGRUPPE:
            if (bruehgruppe->getState() == KOCHEN) {
                coffeeState = CoffeeState::PUMPING_WATER;
                wasserpumpe->pumpeStarten();
                tickCounter = 0;
            }
            qDebug() << "PS: WAB";
            break;

        case CoffeeState::PUMPING_WATER:
            // prüfen ob Wasser fertig gepumpt
            if (tickCounter >= currentProgramm->getWassermenge_ml()/10){
                wasserpumpe->pumpeStoppen();
                milchpumpe->pumpeStarten();
                milchschaeumer->aufschaeumenStarten();
                coffeeState = CoffeeState::PUMPING_MILK;
                tickCounter = 0;
            }
            qDebug() << "PS: PUMPIN_WATER";
            break;
        case CoffeeState::PUMPING_MILK:
            // prüfen ob Milch fertig gepumpt
            if (tickCounter >= currentProgramm->getMilchmenge_ml()/10){
                milchschaeumer->aufschaeumenStoppen();
                milchpumpe->pumpeStoppen();
                zucker->zuckerAuswerfen();
                bruehgruppe->trigger(KOCHENAUFGEHOERT);
                coffeeState = CoffeeState::ZUCKERAUSWERFEN;
                tickCounter = 0;
            }
            qDebug() << "PS: PUMPING_MILK";
            break;

        case CoffeeState::ZUCKERAUSWERFEN:
            if (tickCounter >= currentProgramm->getMitZucker()*5){
                zucker->ausschalten();
                coffeeState = CoffeeState::ZURUECK_SETZEN;
            }
            qDebug() << "PS: ZUCKERAUSWERFWEN";
            break;

        case CoffeeState::ZURUECK_SETZEN:
            if (bruehgruppe->getState() == WARTEN) {
                coffeeState = CoffeeState::IDLE;
                busy = false;
            }
            qDebug() << "PS: ZURUECK_SETZEEN";
            break;

        default:
            break;
        }
        tickCounter++;
    }
