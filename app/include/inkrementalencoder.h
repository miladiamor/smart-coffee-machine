#ifndef INKREMENTALENCODER_H
#define INKREMENTALENCODER_H

#include <QObject>

class Kolbenmotor;

class Inkrementalencoder : public QObject
{
    Q_OBJECT
    public:
        Inkrementalencoder();
        float getPosition_mm();
        void setPosition(float position_mm);

        void setStampfer(Kolbenmotor *stampfer);
    public slots:
        //void update(float neuPosition_mm);

    private:
        float position_mm;
        Kolbenmotor *stampfer;
};

#endif
