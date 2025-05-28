#ifndef ZUCKERDISPENSER_H
#define ZUCKERDISPENSER_H

#include <QObject>
#include <QTimer>
#include <QThread>

class Zuckerdispenser : public QObject {

    Q_OBJECT
    private:
        bool eingeschaltet;
        QTimer sleeper;

    public:
        Zuckerdispenser();
        void zuckerAuswerfen();
        bool istAktiv() const;
        void ausschalten();
}; 

#endif
