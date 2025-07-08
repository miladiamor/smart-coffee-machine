#pragma once
// Diese Klasse repraesentiert ein passives Muenzrohr (Sensor),
// das nur die Anzahl der enthaltenen Muenzen verfolgt.
class Muenzroehre {
private:
    //int kapazitaet;       // Maximale Anzahl an Muenzen, die das Rohr aufnehmen kann
    int aktuelleAnzahl;   // Aktuelle Anzahl an Muenzen im Rohr

public:
    // Konstruktor: Initialisiert Rohr mit Muenzwert und Kapazitaet
    Muenzroehre(int kapazitaet, float wert);

    // Standardkonstruktor für Unittests
    Muenzroehre();  // <-- hinzugefügt

    // Gibt zurueck, ob das Rohr voll ist
    bool istVoll() const;

    // Gibt die aktuelle Anzahl der Muenzen zurueck
    int getAktuelleAnzahl() const;

    // Gibt die maximale Kapazitaet des Rohrs zurueck
    //int getKapazitaet() const;

    // Erhoeht den Muenzzaehler um 1 (z. B. wenn Muenzenschieber eine Muenze hineinschiebt)
    void erhoeheAnzahl();
    void reduziereAnzahl();
};
