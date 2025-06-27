#include <QApplication>
#include "display.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Display display;
    MainWindow mw;
    QObject::connect(&mw, &MainWindow::sentTouch,
                     &display, &Display::acceptTouch,
                    Qt::DirectConnection);

    QObject::connect(&display, &Display::updateDisplay,
                    &mw, &MainWindow::updateWindow,
                     Qt::DirectConnection);

    mw.show();

    return app.exec();
}
