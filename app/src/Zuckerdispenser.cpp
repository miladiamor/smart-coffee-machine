#include "Zuckerdispenser.h"
#include <QDebug>

Zuckerdispenser::Zuckerdispenser(){
    zuckerMenge_g = 10;

}

void Zuckerdispenser::zuckerAuswerfen(){
    if(zuckerMenge_g < 0){
        zuckerMenge_g -= 1;
        qDebug() << "1g Zucker ausgeworfen:" << zuckerMenge_g << "g";
    }
    else{
        qDebug() <<"Kein Zucker mehr vorhanden!";
    }
}

