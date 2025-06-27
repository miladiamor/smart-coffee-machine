#include <QPixmap>
#include <QTouchEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->touchDisplayLabel->setAttribute(Qt::WA_AcceptTouchEvents);
    ui->touchDisplayLabel->installEventFilter(this);

    this->cup = findChild<QProgressBar*>("cup");


    // Initialize and connect Display
    display = new Display(this);
    connect(display, &Display::updateDisplay, this, &MainWindow::updateWindow);

    // Initialize Programmsteuerung and Koordinator
    programmsteuerung = new Programmsteuerung();
    koordinator = new Koordinator();

    // Connect Koordinator with Programmsteuerung and Display
    koordinator->setzeProgrammsteuerung(programmsteuerung);
    koordinator->setzeDisplay(display);

    // Set up periodic updates (every 100 ms)
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateSystem);
    updateTimer->start(100);

    // Connect touch signal to Display
    connect(this, &MainWindow::sentTouch, display, &Display::acceptTouch);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete updateTimer;
    delete koordinator;
    delete programmsteuerung;
    delete display;
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
            emit sentTouch(lastTouch);          // passed to Display
        }
        return true;
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::updateWindow(const QImage &img) {
    QPixmap pm = QPixmap::fromImage(img).scaled(ui->touchDisplayLabel->size(),
                                                Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation);
    ui->touchDisplayLabel->setPixmap(pm);
}


void MainWindow::updateSystem() {
    if (koordinator) {
        koordinator->update();
    }
}

