#ifndef INKREMENTALENCODER_H
#define INKREMENTALENCODER_H

#include <QObject>

class Kolbenmotor;

class Inkrementalencoder : public QObject
{
    Q_OBJECT
public:
        Inkrementalencoder(Kolbenmotor *stampfer);
        int get_position_in_mm();

    public slots:
        void update(int neu_position_mm);

    private:
        int position_mm;
        Kolbenmotor *stampfer;
};

#endif
