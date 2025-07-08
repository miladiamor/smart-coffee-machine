#include "simulation.h"
#include <cmath>
#include <QDebug>

Simulation::Simulation() :
    motorPosition_mm(0),
    kaffeerestbehaelter_g(0),
    kaffeebehaelter_g(0),
    bruehkammerKaffeeinhalt_g(0){}

//Simulation::Simulation() {}


void Simulation::setKaffeerestbehaelter(Tankwaage *kaffeerestbehaelter) {
    this->kaffeerestbehaelter = kaffeerestbehaelter;
}

void Simulation::setKolbenmotor(Kolbenmotor *kolbenmotor){
    this->kolbenmotor = kolbenmotor;
}

void Simulation::setInkrementalencoder(Inkrementalencoder *inkrementalencoder){
    this->inkrementalencoder = inkrementalencoder;
}

void Simulation::setWasserPumpe(Pumpe *pumpe){
    this->wasserpumpe = pumpe;
}

void Simulation::setMilchPumpe(Pumpe *pumpe){
    this->milchpumpe = pumpe;
}

void Simulation::setSchaeumer(Schaeumer *schaeumer) {
    this->schaeumer = schaeumer;
}

// Temperatur und Regler
#define HEIZRATE_WASSER_CEL_PRO_TICK 0.5f  // während der Heizung Temperatur erhöht sich
#define PUMP_MILCH_G_PRO_TICK          8.0f
#define PUMP_WASSER_G_PRO_TICK         11.35f
// Wasser wird in der Kaffee gemwandelt
#define MILCH_MAXTEMP_CEL             65.0f
#define MILCH_STARTTEMP_CEL           25.0f
#define MILCH_HEIZRATE_CEL_PRO_TICK   0.0005f
#define MILCH_KUEHLRATE_CEL_PRO_TICK  0.0003f

// Motorgeschwindigkeit definieren
#define MOTOR_MAX_HEIGHT_MM 25
#define MOTORGESCHWINDIGKEIT_MM_PRO_TICK 0.1
// Kaffeezufuhur
#define KAFFEEZUFUHR_G_PRO_TICK 0.1
// Entleern
#define BEHAELTER_MAX_FUELLSTAND_G 10000

void Simulation::tick(){
    // Motor hoch/runterfahren
    Kolbenmotor::motorStatus mtStatus = kolbenmotor->getStatus();
    if (mtStatus != Kolbenmotor::motorStatus::Aus) {
        if (mtStatus == Kolbenmotor::motorStatus::runterfahren && motorPosition_mm > 0) {
            motorPosition_mm -= MOTORGESCHWINDIGKEIT_MM_PRO_TICK;
            if (motorPosition_mm < 0) {motorPosition_mm = 0;}
        } else if (mtStatus == Kolbenmotor::motorStatus::hochfahren && motorPosition_mm < MOTOR_MAX_HEIGHT_MM) {
            motorPosition_mm += MOTORGESCHWINDIGKEIT_MM_PRO_TICK;
            if (motorPosition_mm > MOTOR_MAX_HEIGHT_MM) {motorPosition_mm = MOTOR_MAX_HEIGHT_MM;}
        }
        inkrementalencoder->setPosition(motorPosition_mm);
    }

    // kaffee entleeren
    if ((motorPosition_mm == 0) && (bruehkammerKaffeeinhalt_g > 0)) {
        if (entleerklappe->get_ist_offen()) {
            kaffeerestbehaelter_g += bruehkammerKaffeeinhalt_g;
            if (kaffeerestbehaelter_g > BEHAELTER_MAX_FUELLSTAND_G) {
                qDebug() << "Simulation: Kaffeerestbehaelter überfüllt";
            }
            kaffeerestbehaelter->setGewicht(kaffeerestbehaelter_g);
        } else {
            qDebug() << "Simulation: Entleerklappe blockt beim Entleeren!";
        }
    }

    // Wasservorwärmung
    if (wasserHeizer->istEingeschaltet()) {
        wasserrohrtemperatur_cel += HEIZRATE_WASSER_CEL_PRO_TICK;
        temperatursensor.setTemperatur_Cel(wasserrohrtemperatur_cel);
        }

    // Milchvorwärmung
    if (milchHeizer->istEingeschaltet()) {
        milchrohrtemperatur_cel += HEIZRATE_WASSER_CEL_PRO_TICK;
        temperatursensor.setTemperatur_Cel(milchrohrtemperatur_cel);
    }

    // Während des Offeneventils fließt das Wasser in den Kaffee
    if (wasserpumpe->get_Aktiv()) {
        if (wasserzufuhrVentil->get_ist_offen() && tropfstopfVentil->get_ist_offen()) {
            float wasserMenge = PUMP_WASSER_G_PRO_TICK * 0.001f;
            wasserbehaelter_g -= wasserMenge;
            kaffeeTassenInhalt_g += wasserMenge;
            wasserbehaelter->setGewicht(wasserbehaelter_g);
        } else {
            qDebug() << "Fehler: Wasser pumpt aber Ventile geschlossen";
        }
    }

    // Milch wird in der Tasse geliefert
    if (milchpumpe->get_Aktiv()) {
        float milchMenge = PUMP_MILCH_G_PRO_TICK * 0.001f;
        float schaumMenge = 0;
        milchbehaelter_g -= milchMenge;
        if (schaeumer->getEingeschaltet()) {
            schaumMenge = milchMenge * 0.1;
            milchSchaum_g += schaumMenge;
            milchMenge *= 0.9;
        }
        kaffeeTassenInhalt_g += milchMenge;
        milchbehaelter->setGewicht(milchbehaelter_g);
    }

    //Zucker
    if (zuckerdispenser->istAktiv()) {
        float zuckermenge = 0.5f;
        kaffeeTassenInhalt_g += zuckermenge;
        zuckerbehaelter_g -= zuckermenge;
        if (zuckerbehaelter) zuckerbehaelter->setGewicht(zuckerbehaelter_g);
    }
}





