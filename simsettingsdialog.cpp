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
    ui->PirateSpinBox->setValue(prob1/100.0);
    ui->CargoSpinBox->setValue(prob2/100.0);
    ui->PatrolSpinBox->setValue(prob3/100.0);
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
        ui->CapturedsExitedLabel->setText(QString::number(cnt.CargosCaptured() -
                                                          (cnt.CapturedsRescued() + cnt.Captureds())));
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
    ui->StartButton->setEnabled(false);

    ui->PirateSpinBox->setEnabled(false);
    ui->CargoSpinBox->setEnabled(false);
    ui->PatrolSpinBox->setEnabled(false);
    if(running)
    {
        //application is in paused state
        emit pause();
    }
    else
    {
        //application is stopped
        int pirateProb = ui->PirateSpinBox->value()*100;
        int cargoProb = ui->CargoSpinBox->value()*100;
        int patrolProb = ui->PatrolSpinBox->value()*100;
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
    ui->StartButton->setEnabled(true);
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
    ui->PirateSpinBox->setEnabled(true);
    ui->CargoSpinBox->setEnabled(true);
    ui->PatrolSpinBox->setEnabled(true);
    {
        ui->CapturedRescueLabel->setText("0");
        ui->CapturedsExitedLabel->setText("0");
        ui->CargoExitLabel->setText("0");
        ui->CargoEnterLabel->setText("0");
        ui->CargosCapturedLabel->setText("0");
        ui->PatrolEnterLabel->setText("0");
        ui->PatrolExitLabel->setText("0");
        ui->PirateEnterLabel->setText("0");
        ui->PirateExitLabel->setText("0");
        ui->PiratesDestroyedLabel->setText("0");
    }
    emit stop();
}
