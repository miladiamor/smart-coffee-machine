#pragma once

// Diese Klasse repraesentiert ein passives Muenzrohr (Sensor),
// das nur die Anzahl der enthaltenen Muenzen verfolgt.
class Muenzroehre {
private:
    float wert;           // Wert der Muenzen, die dieses Rohr enthaelt (z. B. 2.0 fuer 2 Euro)
    int kapazitaet;       // Maximale Anzahl an Muenzen, die das Rohr aufnehmen kann
    int aktuelleAnzahl;   // Aktuelle Anzahl an Muenzen im Rohr

public:
    // Konstruktor: Initialisiert Rohr mit Muenzwert und Kapazitaet
    Muenzroehre(float wert, int kapazitaet);

    // Gibt zurueck, ob das Rohr voll ist
    bool istVoll() const;

    // Leert das Rohr (setzt Anzahl auf 0)
    void leeren();

    // Gibt die aktuelle Anzahl der Muenzen zurueck
    int getAktuelleAnzahl() const;

    // Gibt die maximale Kapazitaet des Rohrs zurueck
    int getKapazitaet() const;

    // Gibt den Wert der Muenzen zurueck, fuer den das Rohr vorgesehen ist
    float getWert() const;

    // Erhoeht den Muenzzaehler um 1 (z. B. wenn Muenzenschieber eine Muenze hineinschiebt)
    void erhoeheAnzahl();
};
