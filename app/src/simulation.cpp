#include "simulation.h"
#include <cmath>

Simulation::Simulation() :
    motorPosition_mm(0),
    kaffeerestbehaelter_fuellstand_g(0),
    kaffeebehaelter_g(0),
    bruehkammerInhalt_g(0),
    kaffeehoehe_mm(0){}

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
    this->schaeumer = schaeumer;
}

static bool wasserResetDone = false;
static bool milchResetDone = false;

// Motorgeschwindigkeit definieren
#define MOTORGESCHWINDIGKEIT_MM_PRO_S 20

void Simulation::update(){
    // Kaffeezufuhr && Kaffeepulverbehältersimulation
    const float kaffee_g_pro_s = 5.7;
    const float hoeheKaffeepulver_mm_pro_g = 0.33;
    const float kaffee_g_pro_frame = kaffee_g_pro_s * 0.001;
    if (inkrementalencoder->getPosition_mm() == MAX_MOTOR_HEIGHT_MM && bruehgruppe->getState() == KAFFEEZUFUHR) {
        bruehkammerInhalt_g += kaffee_g_pro_frame;
        kaffeehoehe_mm += kaffee_g_pro_frame * hoeheKaffeepulver_mm_pro_g;
        kaffeebehaelter_g -= kaffee_g_pro_frame;
    }

    // Motorsimulation & Kaffeerestbehälter
    const float kaffeerest_g_pro_mm = 0.315;
    const float bewegung_pro_frame = MOTORGESCHWINDIGKEIT_MM_PRO_S * std::pow(10, -3);
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
        wassertemperatur_cel += heizrate_cel * 0.001;
    }

    // Sensoren setzen
    inkrementalencoder->setPosition(motorPosition_mm);
    kaffeerestbehaelter->setGewicht(kaffeerestbehaelter_fuellstand_g);
    temperatursensor.setTemperatur_Cel(wassertemperatur_cel);

    //Durchflusssensor & Pumpe
    const float pumpmenge_wasser_pro_s_in_g = 11.35;
    const float pumpmenge_milch_pro_s_in_g = 9.2;

    float wassermenge_pro_frame = pumpmenge_wasser_pro_s_in_g;
    float milchmenge_pro_frame = pumpmenge_milch_pro_s_in_g;

    // Wasserfluss

    if (!wasserResetDone && wasserpumpe->istAktiv() == true) {
        wasserzaehler->setNull();
        wasserResetDone = true;
    }

    wasserzaehler->addWassermenge_g(wassermenge_pro_frame);
    wasserzaehler->setDurchflussImpuls(true);
    wasserzaehler->setDurchflussImpuls(false);

    // Pumpe stoppen bei 150 g wasser
    if (wasserzaehler->getWassermenge_g() >= 150.0) {
        wasserpumpe->pumpeStoppen();
    }

    // Milchfluss

    if (!milchResetDone && milchpumpe->istAktiv() == true) {
        milchzaehler->setNull();
        milchResetDone = true;
    }

    milchzaehler->addWassermenge_g(milchmenge_pro_frame);
    milchzaehler->setDurchflussImpuls(true);
    milchzaehler->setDurchflussImpuls(false);

    // Pumpe stoppen bei 150g milch
    if (milchzaehler->getWassermenge_g() >= 75.0) {
        milchpumpe->pumpeStoppen();
    }


    // Schaeumer
    const float MILCH_STARTTEMP_CEL = 25.0;
    const float MILCH_MAXTEMP_CEL = 65.0;
    const float MILCH_HEIZRATE_CEL_PRO_S = 0.5;
    const float MILCH_KUEHLRATE_CEL_PRO_S = 0.3;
    if (schaeumer && schaeumer->getEingeschaltet() && milchtemperatur_cel < MILCH_MAXTEMP_CEL) {
        milchtemperatur_cel += MILCH_HEIZRATE_CEL_PRO_S;

    } else if (milchtemperatur_cel > MILCH_STARTTEMP_CEL) {
        milchtemperatur_cel -= MILCH_KUEHLRATE_CEL_PRO_S;

        if (milchtemperatur_cel < MILCH_STARTTEMP_CEL) {
            milchtemperatur_cel = MILCH_STARTTEMP_CEL;
        }
    }

    // Zuckerdispenser
    if (!zuckerdispenser.istAktiv()){
        zuckerdispenser.zuckerAuswerfen();
    }
   // zuckerdispenser.update(delta_t_ms);

}

