#include "inkrementalencoder.h"
#include "kolbenmotor.h"

Inkrementalencoder::Inkrementalencoder(Kolbenmotor *stampfer) :
    position_mm(0),
    stampfer(stampfer)
    {}

float Inkrementalencoder::getPosition_mm() {
    return position_mm;
}

void Inkrementalencoder::setPosition(float position_mm) {
    this->position_mm = position_mm;
}

void Inkrementalencoder::update(float neu_position_mm){
    position_mm = neu_position_mm;
}
