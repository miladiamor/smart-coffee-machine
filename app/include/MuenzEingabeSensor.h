#ifndef MUENZEINGABESENSOR_H
#define MUENZEINGABESENSOR_H

class MuenzEingabeSensor {
private:
    float letzteMuenze;

public:
    MuenzEingabeSensor() : letzteMuenze(0.0f) {}

    void simuliereMuenze(float wert) {
        letzteMuenze = wert;
    }

    float getEingeworfeneMuenze() {
        return letzteMuenze;
    }

    float erkenneMuenze() {
        return letzteMuenze;
    }

    bool ungueltigeMuenze() {
        return !(letzteMuenze == 2.0f || letzteMuenze == 1.0f ||
                 letzteMuenze == 0.5f || letzteMuenze == 0.2f ||
                 letzteMuenze == 0.1f);
    }
};

#endif
