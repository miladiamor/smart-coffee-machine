#include "Koordinator.h"

Koordinator::Koordinator(Display* display, Fuellstandsmessung* fsm)
    : display(display), fsm(fsm), ausgewaehltesProgramm(nullptr), mitMilch(false), mitZucker(false), zahlung(nullptr) {}

void Koordinator::auswahlAnzeigen() {
    display->displayFrame();
    Position input = display->getTouchEvent();
    int drinkIndex = input.getX();  // simple logic for choosing a drink
    ausgewaehltesProgramm = new Kaffeeprogramm();  // Simulate a chosen drink
}

void Koordinator::nachMilchFragen() {
    display->showWarning("Moechten Sie Milch?");
    Position input = display->getTouchEvent();
    mitMilch = input.getX() > 0;  // simulate YES if clicked right side
}

void Koordinator::nachZuckerFragen() {
    display->showWarning("Moechten Sie Zucker?");
    Position input = display->getTouchEvent();
    mitZucker = input.getX() > 0;  // simulate YES if clicked right side
}

    bool Koordinator::bezahlen() {
    display->showWarning("Bitte bezahlen Sie jetzt...");

    if (!zahlung || !ausgewaehltesProgramm) {
        display->showWarning("Zahlungssystem nicht verbunden!");
        return false;
    }

    Produkt* produkt = ausgewaehltesProgramm->getProdukt();   // TODO: Bitte in Kaffeeprogramm die Methode getProdukt() implementieren,
                                                             // damit der Koordinator das aktuelle Produkt für die Zahlung abrufen kann.
    bool erfolg = zahlung->versucheZahlung(produkt);

    if (!erfolg) {
        display->showWarning("Zahlung fehlgeschlagen!");
    }
        return true;  // Simulate payment done
    }

Kaffeeprogramm* Koordinator::getAusgewaehltesProgramm() const {
    return ausgewaehltesProgramm;
}

void Koordinator::setZahlungseinheit(Zahlungseinheit* z) {
    zahlung = z;
}
