#pragma once


// Diese Klasse repraesentiert ein passives Muenzrohr (Sensor),
// das nur die Anzahl der enthaltenen Muenzen verfolgt.

class Muenzroehre {
private:

    int aktuelleAnzahl;   // Aktuelle Anzahl an Muenzen im Rohr

public:
    // Konstruktor: Initialisiert Rohr mit Muenzwert und Kapazitaet
    Muenzroehre(int kapazitaet, float wert);

    // Standardkonstruktor für Unittests
    Muenzroehre();

    bool istVoll() const;
    int getAktuelleAnzahl() const;
    void erhoeheAnzahl();
    void reduziereAnzahl();
};
