#include "MuenzAuswerfer.h"

// Standardkonstruktor für Unit-Tests
MuenzAuswerfer::MuenzAuswerfer()
    : aktiveRoehre(nullptr)
{}

void MuenzAuswerfer::auswerfenMuenze(Muenzroehre *aktiveRoehre) {
    aktiveRoehre->reduziereAnzahl();
}
