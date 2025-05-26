#ifndef SCHAEUMER_H
#define SCHAEUMER_H

class Schaeumer {

private:
    bool eingeschaltet;
public:
    Schaeumer();
    bool getEingeschaltet();
    void aufschaeumenStarten();
    void aufschaeumenStoppen();

};

#endif
