#ifndef KOLBENMOTOR_H
#define KOLBENMOTOR_H

class Bruehgruppe;

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
};

#endif
