#pragma once
class Heizregler; // Forward declaration
class Heizelemente {

private:
    bool eingeschaltet;

public:
    Heizelemente();  // Konstruktor
    void einschalten();
    void ausschalten();
    //void heizen(int zieltemperatur);  // Zieltemperatur setzen
    //void heizenStoppen();             // Heizung stoppen
    //int getTemperatur() const;        // aktuelle Temperatur abfragen
};

