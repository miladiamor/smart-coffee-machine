#ifndef SCHAEUMER_H
#define SCHAEUMER_H

#include <QObject>

class Schaeumer : public QObject {
    Q_OBJECT

private:
    bool eingeschaltet;
public:
    Schaeumer() : eingeschaltet(false){}
    bool getEingeschaltet();
    void aufschaeumenStarten();
    void aufschaeumenStoppen();

};

#endif
