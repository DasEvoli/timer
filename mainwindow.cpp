#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Stopwatch *stopwatchObj, QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow),
stopwatchObj(stopwatchObj),
m_pTableWidget(NULL)
{
    ui->setupUi(this);
    setupConnections();
    ui->timer_ms->display(stopwatchObj->getMs());
    ui->timer_s->display(stopwatchObj->getS());
    ui->timer_m->display(stopwatchObj->getM());
    ui->timer_h->display(stopwatchObj->getH());
    // Table for Splits
    m_pTableWidget = ui->splitTable;
    m_pTableWidget->setRowCount(0);
    m_pTableWidget->setColumnCount(3);
    m_TableHeader<<"PLATZ"<<"ZEIT"<<"ANMERKUNG";
    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    m_pTableWidget->verticalHeader()->setVisible(false);
    m_pTableWidget->setShowGrid(false);

    ui->tabWidget->setTabText(0, "Stopwatch");
    ui->tabWidget->setTabText(1, "Alarm Clock");
    ui->tabWidget->setMovable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startTimer()
{
    if(stopwatchObj->getTimeIsRunning() == false){
        stopwatchObj->startTimer();
        ui->b_split->setDisabled(false);
        ui->b_start->setDisabled(true);
        ui->b_stop->setText("Stop");
    }
}

void MainWindow::stopTimer()
{
    if(stopwatchObj->getTimeIsRunning()){
        stopwatchObj->getTimer()->stop();
        stopwatchObj->setTimeIsRunning(false);
        ui->b_split->setDisabled(true);
        ui->b_start->setDisabled(false);
        ui->b_stop->setText("Reset");
    }
    else{
        stopwatchObj->setMs(0);
        stopwatchObj->setS(0);
        stopwatchObj->setM(0);
        stopwatchObj->setH(0);
        emit stopwatchObj->msChanged();
        emit stopwatchObj->sChanged();
        emit stopwatchObj->mChanged();
        emit stopwatchObj->hChanged();
        ui->b_stop->setText("Stop");
    }
}

void MainWindow::splitTimer()
{
    stopwatchObj->addSplit();
    QList<Stopwatch*> splitList = stopwatchObj->getSplits();

    Stopwatch* lastTimeSplit = splitList.last();
    QTime *timeObj = new QTime(lastTimeSplit->getH(), lastTimeSplit->getM(), lastTimeSplit->getS());
    m_pTableWidget->setRowCount(m_pTableWidget->rowCount() + 1);
    m_pTableWidget->setItem(splitList.count() -1, 0, new QTableWidgetItem(QString::number(splitList.count())));
    m_pTableWidget->setItem(splitList.count() -1, 1, new QTableWidgetItem(timeObj->toString() + '.' + QString::number(lastTimeSplit->getMs() / 10)));
}

void MainWindow::clearSplits()
{
    stopwatchObj->clearSplits();
    m_pTableWidget->setRowCount(0);
}

void MainWindow::updateMs()
{
    ui->timer_ms->display(stopwatchObj->getMs() / 10);
}

void MainWindow::updateS()
{
    ui->timer_s->display(stopwatchObj->getS());
}

void MainWindow::updateM()
{
    ui->timer_m->display(stopwatchObj->getM());
}

void MainWindow::updateH()
{
    ui->timer_h->display(stopwatchObj->getH());
}

void MainWindow::saveToFile()
{
    fileStreamObject->saveToFile(stopwatchObj);
}

void MainWindow::setupConnections(){
    connect(ui->b_start, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->b_stop, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(ui->b_split, &QPushButton::clicked, this, &MainWindow::splitTimer);
    connect(ui->b_clear, &QPushButton::clicked, this, &MainWindow::clearSplits);
    connect(stopwatchObj, &Stopwatch::msChanged, this, &MainWindow::updateMs);
    connect(stopwatchObj, &Stopwatch::sChanged, this, &MainWindow::updateS);
    connect(stopwatchObj, &Stopwatch::mChanged, this, &MainWindow::updateM);
    connect(stopwatchObj, &Stopwatch::hChanged, this, &MainWindow::updateH);
    connect(ui->b_save, &QPushButton::clicked, this, &MainWindow::saveToFile);
}
