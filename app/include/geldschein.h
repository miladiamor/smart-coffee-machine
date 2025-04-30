#ifndef GELDSCHEIN_H
#define GELDSCHEIN_H

class Geldschein
{
public:

    Geldschein(float wert);

    float getWert() const;

private:
    float wert;
};

#endif // GELDSCHEIN_H
