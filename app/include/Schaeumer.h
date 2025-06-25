#ifndef SCHAEUMER_H
#define SCHAEUMER_H

class Schaeumer {

private:
    bool eingeschaltet;
public:
    Schaeumer();
    virtual ~Schaeumer();
    virtual bool getEingeschaltet();
    virtual void aufschaeumenStarten();
    virtual void aufschaeumenStoppen();

};

#endif
