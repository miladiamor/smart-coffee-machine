#ifndef MUENZEINGABESENSOR_H
#define MUENZEINGABESENSOR_H

class MuenzEingabeSensor {
private:
    float eingeworfeneMuenze;
    bool muenzeGueltig;
public:
    MuenzEingabeSensor() : eingeworfeneMuenze(0.0f), muenzeGueltig(false) {}
    void setEingeworfeneMuenze(float eingeworfeneMuenze) {
        this->eingeworfeneMuenze = eingeworfeneMuenze;
        muenzeGueltig = !(eingeworfeneMuenze == 2.0f || eingeworfeneMuenze == 1.0f ||
                          eingeworfeneMuenze == 0.5f || eingeworfeneMuenze == 0.2f ||
                          eingeworfeneMuenze == 0.1f);
    }
    float getEingeworfeneMuenze() {return eingeworfeneMuenze;}
    bool getMuenzeGueltig() {return muenzeGueltig;}
};

#endif
