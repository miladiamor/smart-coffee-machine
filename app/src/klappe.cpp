#include "klappe.h"

Klappe::Klappe() : ist_offen(false) {

}

void Klappe::oeffnen() {
    ist_offen = true;
}

void Klappe::schliessen() {
    ist_offen = false;
}

int  Klappe::get_ist_offen() {
    return ist_offen;
}
