#include <thread>
#include <iostream>
#include "inkrementalencoder.h"
#include "kolbenmotor.h"

Inkrementalencoder::Inkrementalencoder(Kolbenmotor *stampfer) :
    position_mm(0),
    stampfer(stampfer),
    th(&Inkrementalencoder::update, this),
    stop(false) {}

int Inkrementalencoder::get_position_in_mm() {
    return position_mm;
}

void Inkrementalencoder::update() {
    using namespace std::chrono_literals;
    while(!stop) {
        switch(stampfer->getStatus()) {
            case 1:
                position_mm -= 1;
                break;
            case 2:
                position_mm += 1;
                break;
            case 3:
                break;
            default:
                std::cerr << "ERROR: Inkrementalencoder konnte den Status des Motors nicht einlesen!\n";
        }

        std::this_thread::sleep_for(10ms);
    }
}
