#ifndef INKREMENTALENCODER_H
#define INKREMENTALENCODER_H

#include <thread>
#include <atomic>

class Kolbenmotor;

class Inkrementalencoder
{
    public:
        Inkrementalencoder(Kolbenmotor *stampfer);
        int get_position_in_mm();
        void update();

    private:
        int position_mm;
        Kolbenmotor *stampfer;
        std::thread th;
        std::atomic<bool> stop;
};

#endif
