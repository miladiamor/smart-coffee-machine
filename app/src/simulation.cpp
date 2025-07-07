#include "simulation.h"
#include <cmath>

Simulation::Simulation() :
    motorPosition_mm(0),
    kaffeerestbehaelter_fuellstand_g(0),
    kaffeebehaelter_g(0),
    bruehkammerKaffeeinhalt_g(0),
    kaffeehoehe_mm(0){}

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
#define PUMP_MILCH_G_PRO_S          8.0f
#define PUMP_WASSER_G_PRO_S         11.35f
// 85 % Wasser wird in der Kaffee gemwandelt
#define KAFFEE_WASSERANTEIL         0.85
#define MILCH_WASSERANTEIL          1.0f
#define MILCH_MAXTEMP_CEL             65.0f
#define MILCH_STARTTEMP_CEL           25.0f
#define MILCH_HEIZRATE_CEL_PRO_TICK   0.0005f
#define MILCH_KUEHLRATE_CEL_PRO_TICK  0.0003f

// Motorgeschwindigkeit definieren
#define MOTORGESCHWINDIGKEIT_MM_PRO_TICK 0.1

void Simulation::tick(){
    /*
    // Kaffeezufuhr && Kaffeepulverbehältersimulation
    const float kaffee_g_pro_s = 5.7;
    const float hoeheKaffeepulver_mm_pro_g = 0.33;
    const float kaffee_g_pro_frame = kaffee_g_pro_s * 0.001;
    if (inkrementalencoder->getPosition_mm() == MAX_MOTOR_HEIGHT_MM) {
        bruehkammerKaffeeinhalt_g += kaffee_g_pro_frame;
        kaffeehoehe_mm += kaffee_g_pro_frame * hoeheKaffeepulver_mm_pro_g;
        kaffeebehaelter_g -= kaffee_g_pro_frame;
    }*/

    /*if (heizregler && heizregler->getEingeschaltet()) {
        wassertemperatur_cel += HEIZRATE_WASSER_CEL_PRO_S;
        if (wassertemperatur_cel > MAX_WASSER_TEMP_CEL)
            wassertemperatur_cel = MAX_WASSER_TEMP_CEL;
    }*/

    // Wasservorwärmung
    if (wasserpumpe && wasserpumpe->get_Aktiv()) {
            wasserrohrtemperatur_cel += HEIZRATE_WASSER_CEL_PRO_TICK;
        }

    // Milchvorwärmung
    if (milchpumpe && milchpumpe->get_Aktiv()) {
        milchrohrtemperatur_cel += HEIZRATE_WASSER_CEL_PRO_TICK;
    }

    // Während des Offeneventils fließt das Wasser in der BG
    if (wasserpumpe && wasserpumpe->get_Aktiv()) {
        if (wasserzufuhrVentil && wasserzufuhrVentil->get_ist_offen()) {
            float wasserMenge = PUMP_WASSER_G_PRO_S * 0.001f;
            bruehkammerKaffeeinhalt_g += wasserMenge;
            wasserbehaelter_g -= wasserMenge;
        }
    }

    // Tropfstoppventil ist offen und genug wasser und Kaffee da ist und dass die Kaffee in der Tasse fließt, wenn Tropfstof vetnil offen ist
    if (tropfstopfVentil && tropfstopfVentil->get_ist_offen()) {
        kaffeeInTasse = bruehkammerKaffeeinhalt_g * KAFFEE_WASSERANTEIL;
        kaffeeTassenInhalt += kaffeeInTasse;
        // Brühkammer wird geleert
        bruehkammerKaffeeinhalt_g = 0;
    }

    // Milch wird in der Tasse geliefert
    if (milchpumpe && milchpumpe->get_Aktiv()) {
        float milchMenge = PUMP_MILCH_G_PRO_S * 0.001f;
        float aktuellerMilchstand = milchbehaelter->gewichtPruefen(); // brauchen wir hier nicht getGewicht
        milchbehaelter->setGewicht(aktuellerMilchstand - milchMenge);
        kaffeeTassenInhalt += milchMenge * MILCH_WASSERANTEIL;
    }

    if (schaeumer) {
        if (schaeumer->getEingeschaltet()) {
            if (milchrohrtemperatur_cel < MILCH_MAXTEMP_CEL) {
                milchrohrtemperatur_cel += MILCH_HEIZRATE_CEL_PRO_TICK;
            }
        } else {
            if (milchrohrtemperatur_cel > MILCH_STARTTEMP_CEL) {
                milchrohrtemperatur_cel -= MILCH_KUEHLRATE_CEL_PRO_TICK;
                if (milchrohrtemperatur_cel < MILCH_STARTTEMP_CEL) {
                    milchrohrtemperatur_cel = MILCH_STARTTEMP_CEL;
                }
            }
        }
    }

    // TemperaturSensor aktualisieren
    //if (temperatursensor)
    //    temperatursensor->setTemperatur_Cel(wassertemperatur_cel);
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

    /*
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
    */



