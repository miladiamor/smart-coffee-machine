#ifndef ZUCKERDISPENSER_H
#define ZUCKERDISPENSER_H

#include <QObject>

class Zuckerdispenser : public QObject {

    Q_OBJECT

    private:
        bool eingeschaltet;

    signals:
        void auswerfenGestartet();
        void auswerfenBeendet();

    public:
        Zuckerdispenser(QObject *parent) : QObject(parent), eingeschaltet(false) {}
        ~Zuckerdispenser() = default;
        bool istAktiv() const;

    public slots:
        void zuckerAuswerfen();
        void ausschalten();
}; 

#endif
