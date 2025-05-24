#ifndef KOLBENMOTOR_H
#define KOLBENMOTOR_H

#include <QObject>
class Bruehgruppe;

class Kolbenmotor : public QObject
{
    Q_OBJECT
    public:
        enum class motorStatus {
            Aus, hochfahren, runterfahren
        };
        Kolbenmotor();
        void runterfahren();
        void hochfahren();
        void stoppen();

        motorStatus getStatus();
    private:
        motorStatus status;
};

#endif
