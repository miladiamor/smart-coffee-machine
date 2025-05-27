#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void cappucino(){

}

void milchkaffee(){

}

void kaffeeCrema(){

}

void latteMachiato(){

}

void zucker(bool mitZucker){

}

void kaufen(){

}
