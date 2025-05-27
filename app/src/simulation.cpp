#include "simulation.h"
#include <cmath>

Simulation::Simulation() : motorPosition_mm(0), kaffeerestbehaelter_fuellstand_g(0) {}

void Simulation::setMilch(Tankwaage *milch) {
    this->milch = milch;
}

void Simulation::setWasser(Tankwaage *wasser) {
    this->wasser = wasser;
}

void Simulation::setKaffee(Tankwaage *kaffee) {
    this->kaffee = kaffee;
}

void Simulation::setZucker(Tankwaage *zucker) {
    this->zucker = zucker;
}

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
    milch->setGewicht(milch->gewichtPruefen());
    wasser->setGewicht(wasser->gewichtPruefen());
    kaffee->setGewicht(kaffee->gewichtPruefen());
    zucker->setGewicht(zucker->gewichtPruefen());
    temperatursensor.setTemperatur_Cel(wassertemperatur_cel);
}


bool Simulation::entnehmeZutat(Tankwaage* tank, int menge, float faktor) {
    float benoetigt = menge * faktor;
    if (tank->hatGenug(benoetigt)) {
        tank->setGewicht(tank->gewichtPruefen() - benoetigt);
        return true;
    }
    return false;
}
