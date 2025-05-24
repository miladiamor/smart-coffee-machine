#ifndef INKREMENTALENCODER_H
#define INKREMENTALENCODER_H

#include <QObject>

class Kolbenmotor;

class Inkrementalencoder : public QObject
{
    Q_OBJECT
    public:
        Inkrementalencoder(Kolbenmotor *stampfer);
        float getPosition();
        void setPosition(float position_mm);

    public slots:
        void update(int neuPosition_mm);

    private:
        float position_mm;
        Kolbenmotor *stampfer;
};

#endif
