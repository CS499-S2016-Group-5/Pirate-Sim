#include "simsettingsdialog.h"
#include "simwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimWindow v;
    SimSettingsDialog w(0,40,25,50);
    QObject::connect(&v, SIGNAL(closed()), &w, SLOT(close()));
    QObject::connect(&w, SIGNAL(closed()), &v, SLOT(close()));

    QObject::connect(&w, SIGNAL(start(int,int,int)), &v, SLOT(startSim(int,int,int)));
    QObject::connect(&w, SIGNAL(stop()), &v, SLOT(stopSim()));
    QObject::connect(&w, SIGNAL(pause()), &v, SLOT(pauseSim()));
    QObject::connect(&w, SIGNAL(update()), &v, SLOT(updateSim()));
    w.show();
    v.show();

    return a.exec();
}
