#include "Zuckerdispenser.h"
#include <QTimer>

Zuckerdispenser::Zuckerdispenser(QObject *parent)
    : QObject(parent), eingeschaltet(false) {}


void Zuckerdispenser::zuckerAuswerfen() {
    if (eingeschaltet) {
        return;
    }
    eingeschaltet = true;
    emit auswerfenGestartet();
    emit auswerfenBeendet();
}

void Zuckerdispenser::ausschalten() {
    eingeschaltet = false;
}

bool Zuckerdispenser::istAktiv() const {
    return eingeschaltet;
}
