#pragma once

class Tankwaage {
private:
    float gewicht_g;

public:
    Tankwaage(float gewicht_g);

    float gewichtPruefen() const;
    void setGewicht(float gewicht_g);


};
