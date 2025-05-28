#include "MuenzEingabeSensor.h"

// Konstruktor initialisiert den Wert auf 0
MuenzEingabeSensor::MuenzEingabeSensor() : wert(0.0f) {}

// Beispielhafte Simulation: erkennt eine Münze und speichert ihren Wert
float MuenzEingabeSensor::erkenneMuenze() {

    wert = 1.0f;
    return wert;
}

// Prüft, ob der erkannte Wert gültig ist
bool MuenzEingabeSensor::ungueltigeMuenze() {
    return !(wert == 2.0f || wert == 1.0f || wert == 0.5f || wert == 0.2f || wert == 0.1f);
}

