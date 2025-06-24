#include <QPixmap>
#include <QTouchEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "display.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->touchDisplayLabel->setAttribute(Qt::WA_AcceptTouchEvents);
    ui->touchDisplayLabel->installEventFilter(this);

    this->cup = findChild<QProgressBar*>("cup");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayScreen(const QImage &img)
{
    // Scale & show your image in the label:
    QPixmap pm = QPixmap::fromImage(img).scaled(ui->touchDisplayLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->touchDisplayLabel->setPixmap(pm);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    QPointF lastTouch;
    if (watched == ui->touchDisplayLabel &&
        (event->type() == QEvent::TouchBegin ||
         event->type() == QEvent::TouchUpdate ||
         event->type() == QEvent::TouchEnd))
    {
        auto *te = static_cast<QTouchEvent*>(event);
        if (!te->points().isEmpty()) {
            lastTouch = te->points().first().position();
            emit sentTouch(lastTouch);
        }
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
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
