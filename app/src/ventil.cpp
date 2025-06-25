#include "ventil.h"

void Ventil::oeffnen() {
    ist_offen = true;
}

void Ventil::schliessen() {
    ist_offen = false;
}

bool Ventil::get_ist_offen() {
    return ist_offen;
}

