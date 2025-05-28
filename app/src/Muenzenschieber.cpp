#include "Muenzenschieber.h"

Muenzenschieber::Muenzenschieber() : aktiveMuenzroehre(nullptr) {}

void Muenzenschieber::schiebeMuenzeInRoehre(Muenzroehre* muenzroehre) {
    aktiveMuenzroehre = muenzroehre;


}

