#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "display.h"

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


void MainWindow::on_btnCappucino_clicked()
{
    display.update(150, 150);
}


void MainWindow::on_btnMilkCoffee_clicked()
{
    display.update(150, 250);
}


void MainWindow::on_btnCoffeeCrema_clicked()
{
    display.update(250, 150);
}


void MainWindow::on_btnLatteMachiato_clicked()
{
    display.update(250, 250);
}

