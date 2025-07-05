#include "MuenzAuswerfer.h"
#include <iostream>

// Standardkonstruktor für Unit-Tests
MuenzAuswerfer::MuenzAuswerfer() {}

void MuenzAuswerfer::auswerfenMuenze(float wert) {
    std::cout << "Wirf eine " << wert << " Euro Muenze aus." << std::endl;
}

void MuenzAuswerfer::auswerfen(float betrag) {
    while (betrag >= 2.0f) {
        auswerfenMuenze(2.0f);
        betrag -= 2.0f;
    }
    while (betrag >= 1.0f) {
        auswerfenMuenze(1.0f);
        betrag -= 1.0f;
    }
    while (betrag >= 0.5f) {
        auswerfenMuenze(0.5f);
        betrag -= 0.5f;
    }
    while (betrag >= 0.2f) {
        auswerfenMuenze(0.2f);
        betrag -= 0.2f;
    }
    while (betrag >= 0.1f) {
        auswerfenMuenze(0.1f);
        betrag -= 0.1f;
    }
}
