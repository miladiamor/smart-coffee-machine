#include <thread>
#include <iostream>
#include "inkrementalencoder.h"
#include "kolbenmotor.h"

Inkrementalencoder::Inkrementalencoder(Kolbenmotor *stampfer) :
    position_mm(0),
    stampfer(stampfer)
    {}

int Inkrementalencoder::get_position_in_mm() {
    return position_mm;
}

void Inkrementalencoder::update(int neu_position_mm){
    position_mm = neu_position_mm;
}
