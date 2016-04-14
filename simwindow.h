#ifndef SIMWINDOW_H
#define SIMWINDOW_H

#include <QDialog>
#include "simsettingsdialog.h"
#include "QCloseEvent"
#include "Simulation.hpp"

namespace Ui {
    class SimWindow;
}

class SimWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimWindow(QWidget *parent = 0);
    ~SimWindow();

public slots:
    Counts updateSim();
    void stopSim();
    void startSim(int pirateProb, int cargoProb, int patrolProb);
    void pauseSim();

signals:
    void closed();

private:
    Ui::SimWindow *ui;
    QPixmap display;
    QPixmap capturedPix;
    QPixmap cargoPix;
    QPixmap patrolPix;
    QPixmap piratePix;
    Simulation *mySim;
    int m_iPirateProb;
    int m_iCargoProb;
    int m_iPatrolProb;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SIMWINDOW_H
