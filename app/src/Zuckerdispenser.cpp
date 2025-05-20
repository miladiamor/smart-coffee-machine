#include "Zuckerdispenser.h"
#include <QDebug>

Zuckerdipenser::Zuckerdipenser(){
    zuckerMenge_g = 10;  // Default menge

}

void Zuckerdipenser::zuckerAuswerfen(){
    if(zuckerMenge_g < 0){
        zuckerMenge_g -= 1;
        qDebug() << "1g Zucker ausgeworfen. Verbleibend:" << zuckerMenge_g << "g";
    }
    else{
        qDebug() <<"Kein Zucker mehr vorhanden!";
    }
}
