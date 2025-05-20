#include "simulation.h"

Simulation::Simulation(Kolbenmotor *kolbenmotor){
    this->kolbenmotor = kolbenmotor;
    motorPosition_mm = 20;
}

void Simulation::update(){
    if (kolbenmotor->getStatus() != Kolbenmotor::motorStatus::Aus) {
        if (kolbenmotor->getStatus() == Kolbenmotor::motorStatus::runterfahren) {
            motorPosition_mm--;
        } else if (kolbenmotor->getStatus() == Kolbenmotor::motorStatus::hochfahren) {
            motorPosition_mm++;
        }
        emit inkrementalencoderUpdate(motorPosition_mm);
    }
}
