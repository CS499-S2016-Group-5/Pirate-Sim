#include "simwindow.h"
#include "ui_simwindow.h"
#include <QTimer>
#include <QPainter>

SimWindow::SimWindow(QWidget *parent) :
    QMainWindow(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::SimWindow)
{
    ui->setupUi(this);
    QPixmap display(1225, 700);
    QPainter p(&display);
    QPixmap pix(":/img/grid.png");
    for(int i = 0; i < 35; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            p.drawPixmap(i*35, j*35, pix);
        }
    }
    ui->label->setPixmap(display);
    mySim = NULL;
}

SimWindow::~SimWindow()
{
    delete ui;
}

void SimWindow::startSim(int pirateProb, int cargoProb, int patrolProb)
{
    mySim = new Simulation(pirateProb, cargoProb, patrolProb);
}
void SimWindow::stopSim()
{
    delete mySim;
    mySim = NULL;
}
Counts SimWindow::updateSim()
{
    Counts retVal;
    //*
    if(mySim != NULL)
    {
        retVal = *mySim->GetCounters();
    }//*/
    return retVal;
}
void SimWindow::pauseSim()
{
    if(mySim != NULL)
    {

    }
}
void SimWindow::closeEvent(QCloseEvent *event)
{
    emit closed();
    event->accept();
}
