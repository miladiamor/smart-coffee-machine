#include "MuenzEingabeSensor.h"
#include <QDebug>

// Standardkonstruktor initialisiert mit 0.0 und ungueltig = false
MuenzEingabeSensor::MuenzEingabeSensor()
    : eingeworfeneMuenze(0.0f), muenzeGueltig(false) {}

void MuenzEingabeSensor::setEingeworfeneMuenze(float eingeworfeneMuenze) {
    this->eingeworfeneMuenze = eingeworfeneMuenze;

    // Nur bestimmte Muenzen gelten als gueltig
    muenzeGueltig = (eingeworfeneMuenze == 2.0f ||
                      eingeworfeneMuenze == 1.0f ||
                      eingeworfeneMuenze == 0.5f ||
                      eingeworfeneMuenze == 0.2f ||
                      eingeworfeneMuenze == 0.1f);

    qDebug() << eingeworfeneMuenze << "gueltig: " << muenzeGueltig;
}

float MuenzEingabeSensor::getEingeworfeneMuenze() {
    return eingeworfeneMuenze;
}

bool MuenzEingabeSensor::getMuenzeGueltig() {
    return muenzeGueltig;
}
