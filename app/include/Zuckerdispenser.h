#ifndef ZUCKERDISPENSER_H
#define ZUCKERDISPENSER_H

#include <QObject>
#include <QTimer>

class Zuckerdispenser : public QObject {

    Q_OBJECT
    private:
        bool eingeschaltet;
        QTimer timer;

    public:
        Zuckerdispenser();
        void zuckerAuswerfen();
        bool istAktiv() const;
}; 

#endif
