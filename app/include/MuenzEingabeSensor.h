#ifndef MUENZEINGABESENSOR_H
#define MUENZEINGABESENSOR_H

class MuenzEingabeSensor {
private:
    float wert;

public:
    MuenzEingabeSensor();

    // Gibt den erkannten Münzwert zurück
    float erkenneMuenze();
    // Prüft, ob es eine gültige Münze ist (nur 2€, 1€, 0.5€, ...)
    bool ungueltigeMuenze();
};

#endif // MUENZEINGABESENSOR_H
