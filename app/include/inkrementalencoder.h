 #pragma once
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

