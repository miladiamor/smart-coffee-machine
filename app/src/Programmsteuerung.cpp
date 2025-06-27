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
    messung(nullptr),
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
            busy = true;
     }

    bool Programmsteuerung::istFertig() const {
        return !busy;
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
                break;

        case CoffeeState::HEIZEN:
            if (temperaturregler_wasser->istTemperaturErreicht() && temperaturregler_milch->istTemperaturErreicht()){// milch hitze prüfen -> milcherhitzer stoppen
                bruehgruppe->trigger(ZUFUHRSTART),// wasserhitze prüfen -> wassererhitzer stoppen
                coffeeState = CoffeeState::KAFFEEZUFUHR;// wenn milch- UND wasserhitze richtig sind (prüfen) ->
                tickCounter = 0;
            }
            break;

        case CoffeeState::KAFFEEZUFUHR:
            if (tickCounter >= currentProgramm->getKaffeemenge_g()/0.3) {
                bruehgruppe->trigger(ZUFUHRABGESCHLOSSEN);
                coffeeState = CoffeeState::WARTENAUFBRUEHGRUPPE;
            }
            break;

        case CoffeeState::WARTENAUFBRUEHGRUPPE:
            if (bruehgruppe->getState() == KOCHEN) {
                coffeeState = CoffeeState::PUMPING_WATER;
                wasserpumpe->pumpeStarten();
                tickCounter = 0;
            }
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
            break;

        case CoffeeState::ZUCKERAUSWERFEN:
            if (tickCounter >= currentProgramm->getMitZucker()*5){
                zucker->ausschalten();
                coffeeState = CoffeeState::ZURUECKSETZEN;
            }

        case CoffeeState::ZURUECKSETZEN:
            if (bruehgruppe->getState() == WARTEN) {
                coffeeState = CoffeeState::IDLE;
                busy = false;
            }
            break;

        default:
            break;
        }
        tickCounter++;
    }
