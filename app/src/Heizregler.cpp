#include "Heizregler.h"
#include <QDebug>
#include "Temperatursensor.h"

Heizregler::Heizregler(){

    zieltemperatur_Cel = 0;
    sensor = nullptr;
    heizen = nullptr;

}

void Heizregler::temperaturRegeln(int Zieltemperatur_Cel){

    zieltemperatur_Cel = Zieltemperatur_Cel;

    if(!sensor || !heizen) return; // Überprüfung, ob sensor und Heizelemente vorhanden sind

    int aktuellTemp = sensor->getTemperatur_Cel();

    if(aktuellTemp < zieltemperatur_Cel){
        heizen->einschalten();
    }
    else{
        heizen->ausschalten();
    }

}

void Heizregler::regelnStoppen(){

    if(heizen){
        heizen->ausschalten();
    }
}
