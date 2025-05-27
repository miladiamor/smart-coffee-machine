#include "simulation.h"
#include <cmath>

Simulation::Simulation() : motorPosition_mm(0), kaffeerestbehaelter_fuellstand_g(0) {}

void Simulation::setKaffeerestbehaelter(Tankwaage *kaffeerestbehaelter) {
    this->kaffeerestbehaelter = kaffeerestbehaelter;
}

void Simulation::setKolbenmotor(Kolbenmotor *kolbenmotor){
    this->kolbenmotor = kolbenmotor;
}

void Simulation::setBruehgruppe(Bruehgruppe *bruehgruppe){
    this->bruehgruppe = bruehgruppe;
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

void Simulation::setWasserzaehler(Durchflusssensor *sensor){
    this->wasserzaehler = sensor;
}

void Simulation::setMilchZaehler(Durchflusssensor *sensor){
    this->milchzaehler = sensor;
}

void Simulation::setSchaeumer(Schaeumer *schaeumer) {
    this->Schaeumer = schaeumer;
}

// Motorgeschwindigkeit definieren
#define MOTORGESCHWINDIGKEIT_MM_PRO_S 20

void Simulation::update(int delta_t_ms){
    // Motorsimulation & Kaffeerestbehälter
    const float kaffeerest_g_pro_mm = 0.315;
    const float bewegung_pro_frame = MOTORGESCHWINDIGKEIT_MM_PRO_S * delta_t_ms * std::pow(10, -3);
    if (kolbenmotor->getStatus() != Kolbenmotor::motorStatus::Aus) {
        if (kolbenmotor->getStatus() == Kolbenmotor::motorStatus::runterfahren && motorPosition_mm < 20) {
            motorPosition_mm += bewegung_pro_frame;
            // Füllstand der Restbehälters
            // füllt sich wenn die Entleerklappe offen ist
            if (bruehgruppe->getEntleerklappeOffen()){
                kaffeerestbehaelter_fuellstand_g += kaffeerest_g_pro_mm * bewegung_pro_frame;
            }
        } else if (kolbenmotor->getStatus() == Kolbenmotor::motorStatus::hochfahren && motorPosition_mm > 0) {
            motorPosition_mm -= bewegung_pro_frame;
        }
    }

    // Temperatur
    const float heizrate_cel = 0.2;
    if (heizregler.getEingeschaltet() == true) {
        wassertemperatur_cel += heizrate_cel * delta_t_ms * 0.001;
    }

    // Sensoren setzen
    inkrementalencoder->setPosition(motorPosition_mm);
    kaffeerestbehaelter->setGewicht(kaffeerestbehaelter_fuellstand_g);
    temperatursensor.setTemperatur_Cel(wassertemperatur_cel);

    //Durchflusssensor & Pumpe
    const float pumpmenge_wasser_pro_s_in_g = 11.35;
    for (int i = 0; i < 50; i++){
        wasserzaehler->setDurchflussImpuls(true);
        wasserzaehler->incrementImpuls();
    }
    wasserzaehler -> setDurchflussImpuls(false);
    wasserpumpe->pumpeStoppen();

    for (int i = 0; i< 50; i++) {
        milchzaehler->setDurchflussImpuls(true);
        milchzaehler->incrementImpuls();
    }
    milchzaehler -> setDurchflussImpuls(false);
    milchpumpe -> pumpeStoppen();

    // Schaeumer
    const float MILCH_STARTTEMP_CEL = 25.0;
    const float MILCH_MAXTEMP_CEL = 65.0;
    const float MILCH_HEIZRATE_CEL_PRO_S = 0.5;
    const float MILCH_KUEHLRATE_CEL_PRO_S = 0.3;
    if (schaeumer && schaeumer->getEingeschaltet() && milchtemperatur_cel < MILCH_MAXTEMP_CEL) {
        milchtemperatur_cel += MILCH_HEIZRATE_CEL_PRO_S * delta_t_ms * 0.001;
/*
        if (milchtemperatur_cel > MILCH_MAXTEMP_CEL) {
            milchtemperatur_cel = MILCH_MAXTEMP_CEL;
        }
*/
    } else if (milchtemperatur_cel > MILCH_STARTTEMP_CEL) {
        milchtemperatur_cel -= MILCH_KUEHLRATE_CEL_PRO_S * delta_t_ms * 0.001;

        if (milchtemperatur_cel < MILCH_STARTTEMP_CEL) {
            milchtemperatur_cel = MILCH_STARTTEMP_CEL;
        }
    }

}

