#pragma once


class Muenzroehre {
private:

    int aktuelleAnzahl;   // Aktuelle Anzahl an Muenzen im Rohr

public:
    // Konstruktor: Initialisiert Rohr mit Muenzwert und Kapazitaet
    Muenzroehre(float wert, int kapazitaet);

    // Standardkonstruktor für Unittests
    Muenzroehre();

    bool istVoll() const;
    int getAktuelleAnzahl() const;
    void erhoeheAnzahl();
    void reduziereAnzahl();
};
