#pragma once

#include "Muenzroehrenspeicher.h"
#include "MuenzEingabeSensor.h"
#include "MuenzAuswerfer.h"
#include "Display.h"

class Zahlungseinheit {
private:
    bool zahlungAktiv = false;             // true if payment process is active
    bool zahlungErfolgreich = false;       // true if payment has been successfully completed
    float gesamterEinwurf = 0.0f;          // amount remaining to be paid
    float preis = 0.0f;                    // total price to be paid

    Muenzroehrenspeicher* speicherVerwaltung = nullptr; // dependency for coin handling
    MuenzEingabeSensor* sensor = nullptr;               // dependency for coin detection
    MuenzAuswerfer* auswerfer = nullptr;                // dependency for coin ejection
    Display* display = nullptr;                         // dependency for user feedback

public:
    // Default constructor for unit tests
    Zahlungseinheit();

    // Constructor with dependencies for integration
    Zahlungseinheit(Muenzroehrenspeicher* speicherVerwaltung,
                    MuenzEingabeSensor* sensor,
                    MuenzAuswerfer* auswerfer);

    // Returns true if the payment was completed successfully
    bool getZahlungErfolgreich();

    // Starts the payment process for a given price
    void versucheZahlung(float preis);

    // Cancels the payment (not implemented yet, placeholder for future extension)
    void zahlungAbbrechen();

    // Processes a tick (one payment step, e.g., handling inserted coins)
    void tick();

    // Injects the display dependency for feedback
    void setDisplay(Display* display);
    void setTestZahlungAktiv(bool aktiv);
};
