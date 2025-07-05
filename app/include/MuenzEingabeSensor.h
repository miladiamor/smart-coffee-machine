#ifndef MUENZEINGABESENSOR_H
#define MUENZEINGABESENSOR_H

class MuenzEingabeSensor {
private:
    float eingeworfeneMuenze;
    bool muenzeGueltig;

public:
    MuenzEingabeSensor();  // Standardkonstruktor

    void setEingeworfeneMuenze(float eingeworfeneMuenze);
    float getEingeworfeneMuenze();
    bool getMuenzeGueltig();

    // Diese wird speziell fuer Unittests verwendet um eine Muenze zu simulieren
    void simuliereMuenze(float wert);
};

#endif
