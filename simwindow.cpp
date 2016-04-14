#include "simwindow.h"
#include "ui_simwindow.h"
#include <QTimer>
#include <QPainter>

SimWindow::SimWindow(QWidget *parent) :
    QMainWindow(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::SimWindow), display(1225, 700),
    capturedPix(":/img/captured_ship_small.png"), cargoPix(":/img/cargo_ship_small.png"), patrolPix(":/img/patrol_ship_small.png"), piratePix(":/img/pirate_ship_small.png")
{
    ui->setupUi(this);
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
    ui->label->setPixmap(display);
    delete mySim;
    mySim = NULL;
}
Counts SimWindow::updateSim()
{
    Counts retVal;
    //*
    if(mySim != NULL)
    {
        mySim->Update();
        retVal = *(mySim->GetCounters());
        Simulation::gridXxYx4 grid = mySim->Grid();

        QPixmap foreground = display;
        QPainter p(&foreground);

        for(int i = 0; i < 35; i++)
        {
            for(int j = 0; j < 20; j++)
            {
                if(grid[i][j][0] != 0)
                {
                    //draw Captured
                    p.drawPixmap(i*35, j*35, capturedPix);
                }
                if(grid[i][j][1] != 0)
                {
                    //draw cargo
                    p.drawPixmap(i*35, j*35, cargoPix);
                }
                if(grid[i][j][2] != 0)
                {
                    //draw patrol
                    p.drawPixmap(i*35, j*35, patrolPix);
                }
                if(grid[i][j][4] != 0)
                {
                    //draw pirate
                    p.drawPixmap(i*35, j*35, piratePix);
                }
                //
            }
        }
        ui->label->setPixmap(foreground);
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
