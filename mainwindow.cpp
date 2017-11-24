#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(timeUnits *timeUnitsObj, QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow),
timeUnitsObj(timeUnitsObj),
m_pTableWidget(NULL)
{
    ui->setupUi(this);
    setupConnections();
    ui->timer_ms->display(timeUnitsObj->getMs());
    ui->timer_s->display(timeUnitsObj->getS());
    ui->timer_m->display(timeUnitsObj->getM());
    ui->timer_h->display(timeUnitsObj->getH());
    // Table for Splits
    m_pTableWidget = ui->splitTable;
    m_pTableWidget->setRowCount(0);
    m_pTableWidget->setColumnCount(3);
    m_TableHeader<<"PLATZ"<<"ZEIT"<<"ANMERKUNG";
    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    m_pTableWidget->verticalHeader()->setVisible(false);
    m_pTableWidget->setShowGrid(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer()
{
    if(timeUnitsObj->getTimeIsRunning() == false){
        timeUnitsObj->startTimer();
        ui->b_split->setDisabled(false);
        ui->b_start->setDisabled(true);
        ui->b_stop->setText("Stop");
    }
}

void MainWindow::stopTimer()
{
    if(timeUnitsObj->getTimeIsRunning()){
        timeUnitsObj->getTimer()->stop();
        timeUnitsObj->setTimeIsRunning(false);
        ui->b_split->setDisabled(true);
        ui->b_start->setDisabled(false);
        ui->b_stop->setText("Reset");
    }
    else{
        timeUnitsObj->setMs(0);
        timeUnitsObj->setS(0);
        timeUnitsObj->setM(0);
        timeUnitsObj->setH(0);
        emit timeUnitsObj->msChanged();
        emit timeUnitsObj->sChanged();
        emit timeUnitsObj->mChanged();
        emit timeUnitsObj->hChanged();
        ui->b_stop->setText("Stop");
    }
}

void MainWindow::splitTimer()
{
    timeUnitsObj->addSplit();
    QList<timeSplit*> splitList = timeUnitsObj->getSplits();

    timeSplit* lastTimeSplit = splitList.last();
    QTime *timeObj = new QTime(lastTimeSplit->getH(), lastTimeSplit->getM(), lastTimeSplit->getS());
    m_pTableWidget->setRowCount(m_pTableWidget->rowCount() + 1);
    m_pTableWidget->setItem(splitList.count() -1, 0, new QTableWidgetItem(QString::number(splitList.count())));
    m_pTableWidget->setItem(splitList.count() -1, 1, new QTableWidgetItem(timeObj->toString() + '.' + QString::number(lastTimeSplit->getMs())));
}

void MainWindow::clearSplits()
{
    timeUnitsObj->clearSplits();
    m_pTableWidget->setRowCount(0);
}

void MainWindow::updateMs()
{
    ui->timer_ms->display(timeUnitsObj->getMs());
}

void MainWindow::updateS()
{
    ui->timer_s->display(timeUnitsObj->getS());
}

void MainWindow::updateM()
{
    ui->timer_m->display(timeUnitsObj->getM());
}

void MainWindow::updateH()
{
    ui->timer_h->display(timeUnitsObj->getH());
}

void MainWindow::saveToFile()
{
    fileStreamObject->saveToFile(timeUnitsObj);
}

void MainWindow::setupConnections(){
    connect(ui->b_start, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->b_stop, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(ui->b_split, &QPushButton::clicked, this, &MainWindow::splitTimer);
    connect(ui->b_clear, &QPushButton::clicked, this, &MainWindow::clearSplits);
    connect(timeUnitsObj, &timeUnits::msChanged, this, &MainWindow::updateMs);
    connect(timeUnitsObj, &timeUnits::sChanged, this, &MainWindow::updateS);
    connect(timeUnitsObj, &timeUnits::mChanged, this, &MainWindow::updateM);
    connect(timeUnitsObj, &timeUnits::hChanged, this, &MainWindow::updateH);
    connect(ui->b_save, &QPushButton::clicked, this, &MainWindow::saveToFile);
}
