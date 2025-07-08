#ifndef MUENZEINGABESENSOR_H
#define MUENZEINGABESENSOR_H

class MuenzEingabeSensor {
private:
    float eingeworfeneMuenze;
    bool muenzeGueltig;
public:
    MuenzEingabeSensor();

    void setEingeworfeneMuenze(float eingeworfeneMuenze);
    float getEingeworfeneMuenze();
    bool getMuenzeGueltig();
};

#endif
