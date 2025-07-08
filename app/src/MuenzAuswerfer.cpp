#include "MuenzAuswerfer.h"

// Standardkonstruktor für Unit-Tests
MuenzAuswerfer::MuenzAuswerfer() {}

void MuenzAuswerfer::auswerfenMuenze(Muenzroehre *aktiveRoehre) {
    aktiveRoehre->reduziereAnzahl();
}
