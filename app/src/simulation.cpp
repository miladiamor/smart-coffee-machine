#include "simulation.h"
#include <cmath>

Simulation::Simulation(Kolbenmotor *kolbenmotor, Bruehgruppe *bruehgruppe) : kolbenmotor(kolbenmotor), bruehgruppe(bruehgruppe), motorPosition_mm(0), kaffeerestbehaelter_fuellstand_g(0) {

}

// Motorgeschwindigkeit definieren
#define MOTORGESCHWINDIGKEIT_MM_PRO_S 20
void Simulation::update(int delta_t_ms){
    // Motorsimulation
    const float bewegung_pro_frame = MOTORGESCHWINDIGKEIT_MM_PRO_S * delta_t_ms * std::pow(10, -3);
    if (kolbenmotor->getStatus() != Kolbenmotor::motorStatus::Aus) {
        if (kolbenmotor->getStatus() == Kolbenmotor::motorStatus::runterfahren && motorPosition_mm < 20) {
            motorPosition_mm += bewegung_pro_frame;
        } else if (kolbenmotor->getStatus() == Kolbenmotor::motorStatus::hochfahren && motorPosition_mm > 0) {
            motorPosition_mm -= bewegung_pro_frame;
        }
    }

    // Füllstand der Restbehälters
    // füllt sich wenn die Entleerklappe offen ist
    const float kaffeerest_pro_mm = 0.315;
    if (bruehgruppe->getEntleerklappeOffen() && kolbenmotor->getStatus() == Kolbenmotor::motorStatus::runterfahren){
        kaffeerestbehaelter_fuellstand_g += kaffeerest_pro_mm * bewegung_pro_frame;
    }
}
