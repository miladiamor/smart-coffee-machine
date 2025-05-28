#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Koordinator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->cup = findChild<QProgressBar*>("cup");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cappucino() {
    auto prog = koordinator->getProgramm();
    // Mengen
    prog->setKaffeemenge_g(9);
    prog->setWassermenge_ml(30);
    prog->setMilchmenge_ml(120);
    // Temperaturen
    prog->setWasserkochhitze(93);
    prog->setMilchkochhitze(65);
}

void MainWindow::milchkaffee() {
    auto prog = koordinator->getProgramm();
    // Mengen
    prog->setKaffeemenge_g(9);
    prog->setWassermenge_ml(30);
    prog->setMilchmenge_ml(150);
    // Temperaturen
    prog->setWasserkochhitze(92);
    prog->setMilchkochhitze(70);
}

void MainWindow::kaffeeCrema() {
    auto prog = koordinator->getProgramm();
    // Mengen
    prog->setKaffeemenge_g(9);
    prog->setWassermenge_ml(80);
    prog->setMilchmenge_ml(0);
    // Temperaturen
    prog->setWasserkochhitze(95);
    prog->setMilchkochhitze(0);
}

void MainWindow::latteMachiato() {
    auto prog = koordinator->getProgramm();
    // Mengen
    prog->setKaffeemenge_g(9);
    prog->setWassermenge_ml(30);
    prog->setMilchmenge_ml(200);
    // Temperaturen
    prog->setWasserkochhitze(92);
    prog->setMilchkochhitze(60);
}


void MainWindow::zucker(bool mitZucker){
    koordinator->getProgramm()->setMitZucker(true);
}

void MainWindow::kaufen(){
    koordinator->bezahlen();
}
