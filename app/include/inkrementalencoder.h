#ifndef INKREMENTALENCODER_H
#define INKREMENTALENCODER_H

#include "kolbenmotor.h"

class InkrementalEncoder
{
    public:
        InkrementalEncoder();
        bool getDrehImpuls();

    private:
        bool drehImpuls;
        Kolbenmotor *motor;
};

#endif // INKREMENTALENCODER_H
