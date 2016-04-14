#include "simsettingsdialog.h"
#include "ui_simsettingsdialog.h"
#include <QTimer>

SimSettingsDialog::SimSettingsDialog(QWidget *parent, int prob1, int prob2, int prob3) :
    QMainWindow(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    ui(new Ui::SimSettingsDialog), m_timer(this)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->prob1 = prob1;
    this->prob2 = prob2;
    this->prob3 = prob3;
    ui->doubleSpinBox->setValue(prob1/100.0);
    ui->doubleSpinBox_2->setValue(prob2/100.0);
    ui->doubleSpinBox_3->setValue(prob3/100.0);
    running = false;
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateSim()));
    //connect(*s)
    //QTimer::singleShot(0, this, SLOT(showDialog()));
}

SimSettingsDialog::~SimSettingsDialog()
{
    delete ui;
}
int SimSettingsDialog::getPirateProb()
{
    return prob1;
}
int SimSettingsDialog::getCargoProb()
{
    return prob2;
}
int SimSettingsDialog::getPatrolProb()
{
    return prob3;
}
void SimSettingsDialog::updateSim()
{
    Counts cnt;
    cnt = emit update();

    {
        ui->CapturedRescueLabel->setText(QString::number(cnt.CapturedsRescued()));
        ui->CargoExitLabel->setText(QString::number(cnt.CargosExited()));
        ui->CargoEnterLabel->setText(QString::number(cnt.CargosEntered()));
        ui->CargosCapturedLabel->setText(QString::number(cnt.CargosCaptured()));
        ui->PatrolEnterLabel->setText(QString::number(cnt.EscortsEntered()));
        ui->PatrolExitLabel->setText(QString::number(cnt.EscortsExited()));
        ui->PirateEnterLabel->setText(QString::number(cnt.PiratesEntered()));
        ui->PirateExitLabel->setText(QString::number(cnt.PiratesExited()));
        ui->PiratesDestroyedLabel->setText(QString::number(cnt.PiratesExited()));
    }
}

void SimSettingsDialog::closeEvent(QCloseEvent *event)
{
    emit closed();
    event->accept();
}
void SimSettingsDialog::on_StartButton_clicked()
{
    ui->StepButton->setEnabled(false);
    ui->PauseButton->setEnabled(true);
    ui->StopButton->setEnabled(true);
    ui->doubleSpinBox->setEnabled(false);
    ui->doubleSpinBox_2->setEnabled(false);
    ui->doubleSpinBox_3->setEnabled(false);
    if(running)
    {
        //application is in paused state
        emit pause();
    }
    else
    {
        //application is stopped
        int pirateProb = ui->doubleSpinBox->value()*100;
        int cargoProb = ui->doubleSpinBox_2->value()*100;
        int patrolProb = ui->doubleSpinBox_3->value()*100;
        emit start(pirateProb, cargoProb, patrolProb);
    }
    running = true;
    m_timer.start(1000);
}

void SimSettingsDialog::on_StepButton_clicked()
{
    updateSim();
}

void SimSettingsDialog::on_PauseButton_clicked()
{
    m_timer.stop();
    ui->PauseButton->setEnabled(false);
    ui->StepButton->setEnabled(true);
}

void SimSettingsDialog::on_StopButton_clicked()
{
    running = false;
    ui->PauseButton->setEnabled(false);
    ui->StepButton->setEnabled(false);
    ui->StopButton->setEnabled(false);
    ui->StartButton->setEnabled(true);
    ui->doubleSpinBox->setEnabled(true);
    ui->doubleSpinBox_2->setEnabled(true);
    ui->doubleSpinBox_3->setEnabled(true);
    emit stop();
}
