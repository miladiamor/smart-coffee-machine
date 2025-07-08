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
#define MOTORGESCHWINDIGKEIT_MM_PRO_TICK 0.1

void Simulation::tick(){
    /*
    // Kaffeezufuhr && Kaffeepulverbehältersimulation
    if (inkrementalencoder->getPosition_mm() == MAX_MOTOR_HEIGHT_MM) {
        bruehkammerKaffeeinhalt_g += kaffee_g_pro_frame;
        kaffeehoehe_mm += kaffee_g_pro_frame * hoeheKaffeepulver_mm_pro_g;
        kaffeebehaelter_g -= kaffee_g_pro_frame;
    }*/

    // Wasservorwärmung
    if (wasserHeizer->istEingeschaltet()) {
            wasserrohrtemperatur_cel += HEIZRATE_WASSER_CEL_PRO_TICK;
        }

    // Milchvorwärmung
    if (milchHeizer->istEingeschaltet()) {
        milchrohrtemperatur_cel += HEIZRATE_WASSER_CEL_PRO_TICK;
    }

    // Während des Offeneventils fließt das Wasser in der BG
    if (wasserpumpe->get_Aktiv()) {
        if (wasserzufuhrVentil->get_ist_offen() && tropfstopfVentil->get_ist_offen()) {
            float wasserMenge = PUMP_WASSER_G_PRO_TICK * 0.001f;
            wasserbehaelter_g -= wasserMenge;
            kaffeeTassenInhalt_g += wasserMenge;
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
    }

    // TemperaturSensor aktualisieren
    temperatursensor.setTemperatur_Cel(wasserrohrtemperatur_cel);
    temperatursensor.setTemperatur_Cel(milchrohrtemperatur_cel);
}

    /*
    // Motorsimulation & Kaffeerestbehälter
    const float kaffeerest_g_pro_mm = 0.315;
    const float bewegung_pro_frame = MOTORGESCHWINDIGKEIT_MM_PRO_S * std::pow(10, -3);
    if (kolbenmotor->getStatus() != Kolbenmotor::motorStatus::Aus) {
        if (kolbenmotor->getStatus() == Kolbenmotor::motorStatus::runterfahren && motorPosition_mm < 20) {
            motorPosition_mm += bewegung_pro_frame;
            // Füllstand der Restbehälters
            // füllt sich wenn die Entleerklappe offen ist
            if (){
                kaffeerestbehaelter_fuellstand_g += kaffeerest_g_pro_mm * bewegung_pro_frame;
            }
        } else if (kolbenmotor->getStatus() == Kolbenmotor::motorStatus::hochfahren && motorPosition_mm > 0) {
            motorPosition_mm -= bewegung_pro_frame;
        }
    }

    */




