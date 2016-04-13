#ifndef SIMSETTINGSDIALOG_H
#define SIMSETTINGSDIALOG_H

#include <QMainWindow>
#include <QTimer>
#include "simwindow.h"
#include "Counts.hpp"

namespace Ui {
class SimSettingsDialog;
}

class SimSettingsDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit SimSettingsDialog(QWidget *parent = 0, int prob1 = 0, int prob2 = 0, int prob3 = 0);
    ~SimSettingsDialog();
    int getPirateProb();
    int getCargoProb();
    int getPatrolProb();

private slots:
    void updateSim();
    void on_StartButton_clicked();

    void on_StepButton_clicked();

    void on_PauseButton_clicked();

    void on_StopButton_clicked();

signals:
    void closed();
    void stop();
    void pause();
    Counts update();
    void start(int pirateProb, int cargoProb, int patrolProb);

private:
    Ui::SimSettingsDialog *ui;
    QTimer m_timer;
    bool running;
    int prob1;
    int prob2;
    int prob3;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // SIMSETTINGSDIALOG_H


