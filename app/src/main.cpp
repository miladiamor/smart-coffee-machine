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

    Bruehgruppe bruehgruppe;
    Clock clock(100);
    Display display;
    Tankwaage wasserbehaelter(5000), kaffeebehaelter(5000), milchbehaelter(5000), kaffeerestbehaelter(0), zuckerbehaelter(500);
    Fuellstandsmessung fuellstandsmessung;
    Ressourcen ressourcen;
    Heizelemente wasserHeizer, milchHeizer;
    Heizregler wasserRegler, milchRegler;
    Temperatursensor wasserTemperatursensor, milchTemperatursensor;
    Inkrementalencoder inkrementalencoder;
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
    Schaeumer schaeumer;
    Simulation simulation;
    Ventil tropfstopfVentil, kaffeezufuhrVentil, wasserzufuhrVentil;
    Zahlungseinheit zahlungseinheit;
    Zuckerdispenser zuckerdispenser;

    // Fuellstandmessung
    fuellstandsmessung.setKaffeeTank(&kaffeebehaelter);
    fuellstandsmessung.setMilchTank(&milchbehaelter);
    fuellstandsmessung.setWasserTank(&wasserbehaelter);
    fuellstandsmessung.setRessourcen(&ressourcen);
    fuellstandsmessung.setZuckerTank(&zuckerbehaelter);

    // Programmsteuerung Komponenten
    programmsteuerung.setMilchschaeumer(&schaeumer);
    programmsteuerung.setBruehgruppe(&bruehgruppe);
    programmsteuerung.setWasserpumpe(&pumpe);
    programmsteuerung.setMilchpumpe(&pumpe);
    programmsteuerung.setWasserHeizer(&wasserRegler);
    programmsteuerung.setMilchHeizer(&milchRegler);
    programmsteuerung.setZuckerdispenser(&zuckerdispenser);

    wasserRegler.setHeizelement(&wasserHeizer);
    milchRegler.setHeizelement(&milchHeizer);
    wasserRegler.setTemperatursensor(&wasserTemperatursensor);
    milchRegler.setTemperatursensor(&milchTemperatursensor);

    motorsteuerung.setStampfer(&kolbenmotor);
    motorsteuerung.setInkrementalencoder(&inkrementalencoder);
    motorsteuerung.setBruehgruppe(&bruehgruppe);
    inkrementalencoder.setStampfer(&kolbenmotor);

    bruehgruppe.setMotorsteuerung(&motorsteuerung);
    bruehgruppe.setWasserzufuhr(&wasserzufuhrVentil);
    bruehgruppe.setKaffeezufuhr(&kaffeezufuhrVentil);
    bruehgruppe.setTropfstopfventil(&tropfstopfVentil);
    bruehgruppe.setEntleerklappe(&klappe);

    koordinator.setzeDisplay(&display);
    koordinator.setzeProgrammsteuerung(&programmsteuerung);
    koordinator.setzeZahlungseinheit(&zahlungseinheit);
    koordinator.setzeFuellstandsmessung(&fuellstandsmessung);

    simulation.setKaffeerestbehaelter(&kaffeerestbehaelter);
    simulation.setWasserbehaelter(&wasserbehaelter);
    simulation.setKaffeebehaelter(&kaffeebehaelter);
    simulation.setMilchbehaelter(&milchbehaelter);
    simulation.setZuckerbehaelter(&zuckerbehaelter);
    simulation.setKolbenmotor(&kolbenmotor);
    simulation.setInkrementalencoder(&inkrementalencoder);
    simulation.setWasserPumpe(&pumpe);
    simulation.setMilchPumpe(&pumpe);
    simulation.setSchaeumer(&schaeumer);
    simulation.setMilchheizer(&milchHeizer);
    simulation.setWasserheizer(&wasserHeizer);
    simulation.setMuenzEingabeSensor(&muenzEingabeSensor);
    simulation.setWasserTemperatursensor(&wasserTemperatursensor);
    simulation.setMilchTemperatursensor(&milchTemperatursensor);
    simulation.setTropfstopfVentil(&tropfstopfVentil);
    simulation.setWasserVentil(&wasserzufuhrVentil);
    simulation.setKaffeeVentil(&kaffeezufuhrVentil);
    simulation.setZuckerdispenser(&zuckerdispenser);
    mw.setSimulation(&simulation);

    muenzroehrenspeicher.setroehre2Euro(&muenzroehre);
    muenzroehrenspeicher.setroehre1Euro(&muenzroehre);
    muenzroehrenspeicher.setroehre50Cent(&muenzroehre);
    muenzroehrenspeicher.setroehre20Cent(&muenzroehre);
    muenzroehrenspeicher.setroehre10Cent(&muenzroehre);
    muenzroehrenspeicher.setschieber(&muenzenschieber);
    muenzroehrenspeicher.setauswerfer(&muenzAuswerfer);
    muenzroehrenspeicher.setsensor(&muenzEingabeSensor);

    muenzenschieber.setMuenzSensor(&muenzEingabeSensor);

    zahlungseinheit.setDisplay(&display);
    zahlungseinheit.setMuenzroehrenspeicher(&muenzroehrenspeicher);
    zahlungseinheit.setMuenzEingabeSensor(&muenzEingabeSensor);
    zahlungseinheit.setMuenzAuswerfer(&muenzAuswerfer);


    QObject::connect(&mw, &MainWindow::sentTouch,
                     &display, &Display::acceptTouch,
                    Qt::DirectConnection);

    QObject::connect(&display, &Display::updateDisplay,
                    &mw, &MainWindow::updateWindow,
                     Qt::DirectConnection);

    QObject::connect(&display, &Display::updateText,
                     &mw, &MainWindow::updateWindowText,
                     Qt::DirectConnection);


    //Simulation und MainWIndow

    QObject::connect(&simulation, &Simulation::setKaffeeInhalt,
                     &mw, &MainWindow::updateKaffee,
                     Qt::DirectConnection);


    //CLOCK
    QObject::connect(&clock, &Clock::update,
                     &koordinator, &Koordinator::tick,
                     Qt::DirectConnection);

    QObject::connect(&clock, &Clock::update,
                     &zahlungseinheit, &Zahlungseinheit::tick,
                     Qt::DirectConnection);

    QObject::connect(&clock, &Clock::update,
                     &programmsteuerung, &Programmsteuerung::tick,
                     Qt::DirectConnection);

    QObject::connect(&clock, &Clock::update,
                     &simulation, &Simulation::tick,
                     Qt::DirectConnection);

    QObject::connect(&clock, &Clock::update,
                     &wasserRegler, &Heizregler::tick,
                     Qt::DirectConnection);

    QObject::connect(&clock, &Clock::update,
                     &milchRegler, &Heizregler::tick,
                     Qt::DirectConnection);

    QObject::connect(&clock, &Clock::update,
                     &motorsteuerung, &Motorsteuerung::tick,
                     Qt::DirectConnection);

    //mw.setSimulation(&simulation);
    //simulation.setMainWindow(&mw);

    mw.show();

    return app.exec();
}
