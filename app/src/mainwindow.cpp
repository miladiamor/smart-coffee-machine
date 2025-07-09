#include <QPixmap>
#include <QTouchEvent>
#include <QMouseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simulation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->touchDisplayLabel->setAttribute(Qt::WA_AcceptTouchEvents);
    ui->touchDisplayLabel->installEventFilter(this);

    this->cup = findChild<QProgressBar*>("cup");
    ui->cup->setRange(0, 350);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    QPointF lastTouch;
    if (watched == ui->touchDisplayLabel && event->type() == QEvent::MouseButtonPress)
    {
        auto *me = static_cast<QMouseEvent*>(event);
        lastTouch = me->position();
        emit sentTouch(lastTouch);
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::updateWindow(const QImage &img) {
    QPixmap pm = QPixmap::fromImage(img).scaled(ui->touchDisplayLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->touchDisplayLabel->clear();
    ui->touchDisplayLabel->setPixmap(pm);
}

void MainWindow::updateWindowText(QString text){
    ui->touchDisplayLabel->clear();
    ui->touchDisplayLabel->setText(text);
}

/*
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

*/

void MainWindow::setSimulation(Simulation *sim) {
    this->sim = sim;
}
/*
void MainWindow::setKaffee(float kaffee)
{
    ui->cup->setValue((int)kaffee);
}
*/
void MainWindow::on_pushButton_2_released()
{
    sim->setMuenze_EUR(1.0f);
}


void MainWindow::on_pushButton_clicked()
{
    sim->setMuenze_EUR(2.0f);
}

