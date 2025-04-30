#ifndef SCHAEUMER_H
#define SCHAEUMER_H

class Schaeumer {
private:
    void aufschaeumenStarten();
    void aufschaeumenStoppen();

public:
    Schaeumer(); // Konstuktor
    void start();
    void stop();
};

#endif // SCHAEUMER_H
