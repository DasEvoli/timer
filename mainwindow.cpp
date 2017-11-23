#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(timeUnits *m_timeObject, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timeObject(m_timeObject),
    m_pTableWidget(NULL)
{
    ui->setupUi(this);
    setup_connections();
    QStringList m_TableHeader;
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

void MainWindow::start_timer()
{
    if(timeObject->getTimeIsRunning() == false){
        timeObject->start_timer();
        ui->b_split->setDisabled(false);
        ui->b_start->setDisabled(true);
        ui->b_stop->setText("Stop");
    }


}

void MainWindow::stop_timer()
{
    if(timeObject->getTimeIsRunning() == true){
        timeObject->getTimer()->stop();
        timeObject->setTimeIsRunning(false);
        ui->b_split->setDisabled(true);
        ui->b_start->setDisabled(false);
        ui->b_stop->setText("Reset");
    }
    else{
        timeObject->setMs(0);
        timeObject->setS(0);
        timeObject->setM(0);
        timeObject->setH(0);
        emit timeObject->ms_changed();
        emit timeObject->s_changed();
        emit timeObject->m_changed();
        emit timeObject->h_changed();
        ui->b_stop->setText("Stop");
    }
}

void MainWindow::split_timer()
{
    timeObject->addSplit();

    QList<timeSplit*> splitList = timeObject->getSplits();
    timeSplit* timeSplitObj = splitList.last();
    QString msString = QString::number(timeSplitObj->getMs());
    QTime *timeObj = new QTime(timeSplitObj->getH(), timeSplitObj->getM(), timeSplitObj->getS());
    QString timeStr = timeObj->toString();

    m_pTableWidget->setRowCount(m_pTableWidget->rowCount() + 1);
    m_pTableWidget->setItem(splitList.count() -1, 0, new QTableWidgetItem(QString::number(splitList.count())));
    m_pTableWidget->setItem(splitList.count() -1, 1, new QTableWidgetItem(timeStr + '.' + msString));

}

void MainWindow::clear_splits()
{
    timeObject->clearSplits();
    m_pTableWidget->setRowCount(0);
}

void MainWindow::update_ms()
{
    ui->timer_ms->display(timeObject->getMs());
}

void MainWindow::update_s()
{
    ui->timer_s->display(timeObject->getS());
}

void MainWindow::update_m()
{
    ui->timer_m->display(timeObject->getM());
}

void MainWindow::update_h()
{
    ui->timer_h->display(timeObject->getH());
}

void MainWindow::saveToFile()
{
    fileObject->saveToFile(timeObject);
}

void MainWindow::setup_connections(){
connect(ui->b_start, &QPushButton::clicked, this, &MainWindow::start_timer);
connect(ui->b_stop, &QPushButton::clicked, this, &MainWindow::stop_timer);
connect(ui->b_split, &QPushButton::clicked, this, &MainWindow::split_timer);
connect(ui->b_clear, &QPushButton::clicked, this, &MainWindow::clear_splits);
connect(timeObject, &timeUnits::ms_changed, this, &MainWindow::update_ms);
connect(timeObject, &timeUnits::s_changed, this, &MainWindow::update_s);
connect(timeObject, &timeUnits::m_changed, this, &MainWindow::update_m);
connect(timeObject, &timeUnits::h_changed, this, &MainWindow::update_h);
connect(ui->b_save, &QPushButton::clicked, this, &MainWindow::saveToFile);
}
