#ifndef KOLBENMOTOR_H
#define KOLBENMOTOR_H

#include "bruehgruppe.h"
class Kolbenmotor
{
    public:
        Kolbenmotor();
        void runterfahren();
        void hochfahren();
        void stoppen();

        int getStatus();
    private:
        int status;
        Bruehgruppe &bruehG;
};

#endif // KOLBENMOTOR_H
