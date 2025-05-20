#include "schaeumer.h"
#include <QDebug>

Schaeumer::Schaeumer() {
}

void Schaeumer::aufschaeumenStarten() {
    qDebug() << "Milchschaumvorgang gestartet.";
}

void Schaeumer::aufschaeumenStoppen() {
    qDebug() << "Milchschaumvorgang gestoppt.";
}
