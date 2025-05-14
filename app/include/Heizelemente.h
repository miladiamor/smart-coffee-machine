#pragma once
class Heizregler; // Forward declaration
class Heizelemente {
    friend class Heizregler;
private:
    int temperatur_Cel;
    int zieltemperatur_Cel;

    void einschalten();
    void ausschalten();

public:
    Heizelemente();  // Konstruktor

    //void heizen(int zieltemperatur);  // Zieltemperatur setzen
    //void heizenStoppen();             // Heizung stoppen
    //int getTemperatur() const;        // aktuelle Temperatur abfragen
};

