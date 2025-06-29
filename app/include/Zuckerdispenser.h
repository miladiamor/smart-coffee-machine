#ifndef ZUCKERDISPENSER_H
#define ZUCKERDISPENSER_H

#include <QObject>

class Zuckerdispenser : public QObject {

    Q_OBJECT

    private:
        bool eingeschaltet;

   /* signals:
        void auswerfenGestartet();
        void auswerfenBeendet();*/

    public:
        Zuckerdispenser() : eingeschaltet(false){}//(QObject *parent = nullptr);
        //~Zuckerdispenser();
        bool istAktiv() const;

    public slots:
        void zuckerAuswerfen();
        void ausschalten();
}; 

#endif
