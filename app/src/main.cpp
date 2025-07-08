#include <QApplication>
#include "Rezept.h"
#include "ausgabeeinheit.h"
#include "bruehgruppe.h"
#include "clock.h"
#include "display.h"
#include "Fuellstandsmessung.h"
#include "Heizelemente.h"
#include "Heizregler.h"
#include "inkrementalencoder.h"
#include "kaffeeprogramm.h"
#include "klappe.h"
#include "kolbenmotor.h"
#include "Koordinator.h"
#include "mainwindow.h"
#include "motorsteuerung.h"
#include "MuenzAuswerfer.h"
#include "MuenzEingabeSensor.h"
#include "Muenzenschieber.h"
#include "muenzroehre.h"
#include "muenzroehrenspeicher.h"
#include "Programmsteuerung.h"
#include "Pumpe.h"
#include "Ressourcen.h"
#include "Schaeumer.h"
#include "simulation.h"
#include "Tankwaage.h"
#include "Temperatursensor.h"
#include "ventil.h"
#include "Zahlungseinheit.h"
#include "Zuckerdispenser.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Ausgabeeinheit ausgabeeinheit;
    Bruehgruppe bruehgruppe;
    Clock clock(100);
    Display display;
    Fuellstandsmessung fuellstandsmessung;
    Heizelemente heizelemente;
    Heizregler heizregler;
    Inkrementalencoder inkrementalencoder;
    Kaffeeprogramm kaffeeprogramm;
    Klappe klappe;
    Kolbenmotor kolbenmotor;
    Koordinator koordinator;
    MainWindow mw;
    Motorsteuerung motorsteuerung;
    MuenzAuswerfer muenzAuswerfer;
    MuenzEingabeSensor muenzEingabeSensor;
    Muenzenschieber muenzenschieber;
    Muenzroehre muenzroehre;
    Muenzroehrenspeicher muenzroehrenspeicher;
    Programmsteuerung programmsteuerung;
    Pumpe pumpe;
    Ressourcen ressourcen;
    Schaeumer schaeumer;
    Simulation simulation;
    Tankwaage tankwaage(0.0f);
    Temperatursensor temperatursensor;
    Ventil ventil;
    Zahlungseinheit zahlungseinheit;
    Zuckerdispenser zuckerdispenser;

    // Komponenten
    programmsteuerung.setMilchschaeumer(&schaeumer);
    programmsteuerung.setBruehgruppe(&bruehgruppe);
    programmsteuerung.setWasserpumpe(&pumpe);
    programmsteuerung.setMilchpumpe(&pumpe);
    programmsteuerung.setWasserHeizer(&heizregler);
    programmsteuerung.setMilchHeizer(&heizregler);
    programmsteuerung.setZuckerdispenser(&zuckerdispenser);

    motorsteuerung.setStampfer(&kolbenmotor);
    motorsteuerung.setInkrementalencoder(&inkrementalencoder);
    motorsteuerung.setBruehgruppe(&bruehgruppe);

    bruehgruppe.setKaffeeprogramm(&kaffeeprogramm);
    bruehgruppe.setMotorsteuerung(&motorsteuerung);
    bruehgruppe.setWasserzufuhr(&ventil);
    bruehgruppe.setKaffeezufuhr(&ventil);
    bruehgruppe.setTropfstopfventil(&ventil);
    bruehgruppe.setEntleerklappe(&klappe);

    koordinator.setzeDisplay(&display);
    koordinator.setzeProgrammsteuerung(&programmsteuerung);
    koordinator.setzeZahlungseinheit(&zahlungseinheit);
    koordinator.setzeFuellstandsmessung(&fuellstandsmessung);

    inkrementalencoder.setStampfer(&kolbenmotor);

    kaffeeprogramm.setBenoetigteRessourcen(ressourcen);

    simulation.setKaffeerestbehaelter(&tankwaage);
    simulation.setKolbenmotor(&kolbenmotor);
    simulation.setBruehgruppe(&bruehgruppe);
    simulation.setInkrementalencoder(&inkrementalencoder);
    simulation.setWasserPumpe(&pumpe);
    simulation.setMilchPumpe(&pumpe);
    simulation.setSchaeumer(&schaeumer);

    zahlungseinheit.setDisplay(&display);

    QObject::connect(&mw, &MainWindow::sentTouch,
                     &display, &Display::acceptTouch,
                    Qt::DirectConnection);

    QObject::connect(&display, &Display::updateDisplay,
                    &mw, &MainWindow::updateWindow,
                     Qt::DirectConnection);

    mw.show();

    return app.exec();
}
