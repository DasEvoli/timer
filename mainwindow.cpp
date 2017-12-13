#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Stopwatch *stopwatchObj, QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow),
stopwatchObj(stopwatchObj)
{
    AlarmControllerObject = new AlarmController();
    ui->setupUi(this);

    //Table for Splits
    m_pTableWidget = ui->splitTable;
    m_pTableWidget->setRowCount(0);
    m_pTableWidget->setColumnCount(3);
    m_TableHeader<<"RANK"<<"TIME"<<"COMMENT";
    m_pTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    m_pTableWidget->verticalHeader()->setVisible(false);
    m_pTableWidget->setShowGrid(true);
    //Tabs for features
    ui->tabWidget->setTabText(0, "Stopwatch");
    ui->tabWidget->setTabText(1, "Alarm Clock");
    ui->tabWidget->setMovable(true);
    //Add Button for a new Alarm
    b_addAlarm = new QPushButton(ui->page);
    b_addAlarm->setText("Add Alarm");
    ui->gridLayout_4->addWidget(b_addAlarm, 1,0,1,1);
    ui->verticalLayout_9->setAlignment(Qt::AlignTop);
    //Default Widget at start
    ui->stackedWidget->setCurrentIndex(0);
    //setup Connections from mainwindow.ui
    setupConnections();
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

void MainWindow::editAlarm(QWidget* widget)
{
    QWidget *parent = ui->alarm_widget_list_contents;
    QObjectList childs = parent->children();
    QList<Alarm*> alarmObjectList = AlarmControllerObject->getObjects();

    ui->stackedWidget->setCurrentIndex(1);

    for(int i = 1; i < childs.count(); i++){
        //find the right child for widget argument
        if(widget == childs[i]){
            //setup the right time in edit window from object
            ui->alarm_h->display(QString::number(alarmObjectList[i-1]->getH()));
            ui->alarm_m->display(QString::number(alarmObjectList[i-1]->getM()));
            ui->sound_alarm->setText(alarmObjectList[i-1]->getSoundFileName());
            //currentAlarmObj needed for saveAlarm and other functions in edit window
            currentAlarmObj = alarmObjectList[i-1];
            //To update the last edited widget on alarm window
            lastEditedWidget = widget;
        }
    }
}

void MainWindow::alarmHUp()
{
   int value = ui->alarm_h->value();

   if(value >= 23) ui->alarm_h->display(0);
   else ui->alarm_h->display(++value);
}

void MainWindow::alarmMUp()
{
    int value = ui->alarm_m->value();

    if(value >= 59) ui->alarm_m->display(0);
    else ui->alarm_m->display(++value);
}

void MainWindow::alarmHDown()
{
    int value = ui->alarm_h->value();

    if(value <= 0) ui->alarm_h->display(23);
    else ui->alarm_h->display(--value);
}

void MainWindow::alarmMDown()
{
    int value = ui->alarm_m->value();

    if(value <= 0) ui->alarm_m->display(59);
    else ui->alarm_m->display(--value);
}

void MainWindow::saveAlarm()
{
    currentAlarmObj->setH(ui->alarm_h->value());
    currentAlarmObj->setM(ui->alarm_m->value());
    currentAlarmObj->setAlarmSound(ui->sound_alarm->text());
    //Update alarmdisplay in window where all others alarms are
    updateEditedAlarmInWindow();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::cancelAlarmEdit()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::openTriggeredAlarmWindow(Alarm* obj)
{
    //if triggeredAlarmWindow isn't destroyed, destroy it now, by declaring it to a nullptr
    if(trAlWin != nullptr){
        trAlWin = nullptr;
    }
    //new window gets created (Widget Parent)
    trAlWin = new TriggeredAlarmWindow(obj, AlarmControllerObject);
}

void MainWindow::toggleWeekday(QWidget* button)
{
    Alarm* alarmObj;
    QString buttonActitvatedStyleSheet = "background-color: gray";
    QString buttonDeactivatedStyleSheet = "background-color: white";
    QObjectList frames = ui->alarm_widget_list_contents->children();
    QObjectList frameContentChilds = frames[1]->children().at(0)->children();
    //Frame (parent) from called button
    QObject *buttonFrame = button->parent()->parent();

    //i = 1 because frames[0] is the gridlayout. Because of that index of alarmcontrollerobject needs to be minus 1
    for(int i = 1; i < frames.count(); i++){
        if(buttonFrame == frames[i]){
            alarmObj = AlarmControllerObject->getObjects().at(i-1);
        }
    }

    for(int i = 0; i < frameContentChilds.count(); i++){
        if(button->objectName() == frameContentChilds[i]->objectName()){
            if(button->objectName() == "b_monday"){
                if(button->styleSheet() == buttonActitvatedStyleSheet){
                    alarmObj->removeWeekday(Alarm::MONDAY);
                    button->setStyleSheet(buttonDeactivatedStyleSheet);
                }
                else{
                    alarmObj->addWeekday(Alarm::MONDAY);
                    button->setStyleSheet(buttonActitvatedStyleSheet);
                }
            }
            if(button->objectName() == "b_tuesday"){
                if(button->styleSheet() == buttonActitvatedStyleSheet){
                    alarmObj->removeWeekday(Alarm::TUESDAY);
                    button->setStyleSheet(buttonDeactivatedStyleSheet);
                }
                else{
                    alarmObj->addWeekday(Alarm::TUESDAY);
                    button->setStyleSheet(buttonActitvatedStyleSheet);
                }
            }
            if(button->objectName() == "b_wednesday"){
                if(button->styleSheet() == buttonActitvatedStyleSheet){
                    alarmObj->removeWeekday(Alarm::WEDNESDAY);
                    button->setStyleSheet(buttonDeactivatedStyleSheet);
                }
                else{
                    alarmObj->addWeekday(Alarm::WEDNESDAY);
                    button->setStyleSheet(buttonActitvatedStyleSheet);
                }
            }
            if(button->objectName() == "b_thursday"){
                if(button->styleSheet() == buttonActitvatedStyleSheet){
                    alarmObj->removeWeekday(Alarm::THURSDAY);
                    button->setStyleSheet(buttonDeactivatedStyleSheet);
                }
                else{
                    alarmObj->addWeekday(Alarm::THURSDAY);
                    button->setStyleSheet(buttonActitvatedStyleSheet);
                }
            }
            if(button->objectName() == "b_friday"){
                if(button->styleSheet() == buttonActitvatedStyleSheet){
                    alarmObj->removeWeekday(Alarm::FRIDAY);
                    button->setStyleSheet(buttonDeactivatedStyleSheet);
                }
                else {
                    alarmObj->addWeekday(Alarm::FRIDAY);
                    button->setStyleSheet(buttonActitvatedStyleSheet);
                }
            }
            if(button->objectName() == "b_saturday"){
                if(button->styleSheet() == buttonActitvatedStyleSheet){
                    alarmObj->removeWeekday(Alarm::SATURDAY);
                    button->setStyleSheet(buttonDeactivatedStyleSheet);
                }
                else{
                    alarmObj->addWeekday(Alarm::SATURDAY);
                    button->setStyleSheet(buttonActitvatedStyleSheet);
                }
            }
            if(button->objectName() == "b_sunday"){
                if(button->styleSheet() == buttonActitvatedStyleSheet){
                    alarmObj->removeWeekday(Alarm::SUNDAY);
                    button->setStyleSheet(buttonDeactivatedStyleSheet);
                }
                else{
                    alarmObj->addWeekday(Alarm::SUNDAY);
                    button->setStyleSheet(buttonActitvatedStyleSheet);
                }
            }
        }
    }
}

void MainWindow::deleteAlarm(QWidget* button)
{
    QObjectList childs = ui->alarm_widget_list_contents->children();

    for(int i = 1; i < childs.count(); i++){
        if(button == childs[i]){
            AlarmControllerObject->deleteAlarm(AlarmControllerObject->getObjects().at(i-1));
            delete childs[i];
        }
    }
}

void MainWindow::loadSound()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,"Load Soundfile", "C:\\Users\\Laura\\Music", "Sound (*.wav)");

    ui->sound_alarm->setText(fileName);
}

void MainWindow::updateEditedAlarmInWindow()
{
    //Updates the last alarm that got just edited
    QLabel* label = lastEditedWidget->findChild<QLabel*>("labelTime");
    QString HString;
    QString MString;
    //add a 0 to the beginning if number is smaller than 9. (There could be a better solution)
    if(currentAlarmObj->getH() <= 9) HString = "0" + QString::number(currentAlarmObj->getH());
    else HString = QString::number(currentAlarmObj->getH());

    if(currentAlarmObj->getM() <= 9) MString = "0" + QString::number(currentAlarmObj->getM());
    else MString = QString::number(currentAlarmObj->getM());

    label->setText(HString + ':' + MString);
}

void MainWindow::closeEvent(QCloseEvent *)
{
    qApp->quit();
}

void MainWindow::addAlarmWidget()
{
    QList<QPushButton*> dayButtons;
    //new frame with content
    QFrame* alarmFrame = new QFrame(ui->alarm_widget_list_contents);
    QGroupBox* frameContent = new QGroupBox(alarmFrame);
    QVBoxLayout* frameContentLayout = new QVBoxLayout();
    QGridLayout* gridLayout = new QGridLayout(frameContent);
    ui->gridLayout_5->addWidget(alarmFrame, ui->gridLayout_5->rowCount(),0,1,1);
    alarmFrame->setLayout(frameContentLayout);
    alarmFrame->setFrameShape(QFrame::Box);
    alarmFrame->setLineWidth(1);
    alarmFrame->setMaximumSize(100000,100);
    alarmFrame->setMinimumHeight(100);
    frameContent->setObjectName("frameContent");
    frameContentLayout->addWidget(frameContent);
    frameContentLayout->setMargin(0);

    //timedisplay
    QLabel* labelTime = new QLabel(frameContent);
    QFont timeFont( "Arial", 20, QFont::Bold);
    labelTime->setText("00:00");
    labelTime->setFont(timeFont);
    labelTime->setMinimumHeight(70);
    labelTime->setObjectName("labelTime");
    gridLayout->addWidget(labelTime, 1, 0, 1, 1);

    //weekday buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    gridLayout->addLayout(buttonLayout, 0, 0, 1, 1);

    //create buttons with values
    for(int i = 0; i < 7; i++){
        QPushButton* b = new QPushButton(frameContent);
        buttonLayout->addWidget(b);
        b->setMinimumWidth(30);
        b->setStyleSheet("background-color: white");
        dayButtons.append(b);

        switch(i){
        case 0: b->setText("Mo");
                b->setObjectName("b_monday");
            break;
        case 1: b->setText("Tu");
                b->setObjectName("b_tuesday");
            break;
        case 2: b->setText("We");
                b->setObjectName("b_wednesday");
            break;
        case 3: b->setText("Th");
                b->setObjectName("b_thursday");
            break;
        case 4: b->setText("Fr");
                b->setObjectName("b_friday");
            break;
        case 5: b->setText("Sa");
                b->setObjectName("b_saturday");
            break;
        case 6: b->setText("Su");
                b->setObjectName("b_sunday");
            break;
        }
    }

    //button for delete
    QPushButton* b_remove_alarm = new QPushButton(frameContent);
    gridLayout->addWidget(b_remove_alarm, 0,1,1,1, Qt::AlignRight);
    b_remove_alarm->setText("X");
    b_remove_alarm->setMaximumWidth(25);
    //signalmapper to get the widget where button was clicked and send it as argument to slot
    QSignalMapper* signalRemove = new QSignalMapper(this);
    connect(signalRemove, SIGNAL(mapped(QWidget*)), this, SLOT(deleteAlarm(QWidget*)));
    connect(b_remove_alarm, SIGNAL(clicked()), signalRemove, SLOT(map()));
    signalRemove->setMapping(b_remove_alarm, alarmFrame);

    //button for edit
    QPushButton* b_open_edit = new QPushButton(frameContent);
    gridLayout->addWidget(b_open_edit, 2,1,1,1);
    b_open_edit->setText("Edit");
    b_open_edit->setMaximumWidth(50);
    //signalmapper to get the widget where button was clicked and send it as argument to slot
    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(QWidget*)), this, SLOT(editAlarm(QWidget*)));
    connect(b_open_edit, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(b_open_edit, alarmFrame);

    //Neues Alarmobjekt + hinzufügen zur Alarmliste
    //TODO: WRITE CONSTRUCTOR FOR ALARM
    Alarm* alarmObj = new Alarm();
    alarmObj->setH(0);
    alarmObj->setM(0);

    //timer who controlls all timers starts if it's the first alarm
    //TODO: STOP ALARMTIMER IF NO ALARMS ARE SET
    AlarmControllerObject->addAlarm(alarmObj);
    if(AlarmControllerObject->getTimerRunning() == false){
        AlarmControllerObject->startAlarmTimer();
    }

    //Signalmapper for all Weekbuttons
    for(int i = 0; i < 7; i++){
        QSignalMapper* signalButtons = new QSignalMapper(this);
        connect(dayButtons[i], SIGNAL(clicked()), signalButtons, SLOT(map()));
        signalButtons->setMapping(dayButtons[i], dayButtons[i]);
        connect(signalButtons, SIGNAL(mapped(QWidget*)), this, SLOT(toggleWeekday(QWidget*)));
    }
}

void MainWindow::setupConnections(){
    connect(ui->b_start, &QPushButton::clicked, this, &MainWindow::startTimer);
    connect(ui->b_stop, &QPushButton::clicked, this, &MainWindow::stopTimer);
    connect(ui->b_split, &QPushButton::clicked, this, &MainWindow::splitTimer);
    connect(ui->b_clear, &QPushButton::clicked, this, &MainWindow::clearSplits); //zurück ändern (war zum probieren)
    connect(stopwatchObj, &Stopwatch::msChanged, this, &MainWindow::updateMs);
    connect(stopwatchObj, &Stopwatch::sChanged, this, &MainWindow::updateS);
    connect(stopwatchObj, &Stopwatch::mChanged, this, &MainWindow::updateM);
    connect(stopwatchObj, &Stopwatch::hChanged, this, &MainWindow::updateH);
    connect(ui->b_save, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(b_addAlarm, &QPushButton::clicked, this, &MainWindow::addAlarmWidget);
    connect(ui->b_alarm_h_up, &QPushButton::clicked, this, &MainWindow::alarmHUp);
    connect(ui->b_alarm_m_up, &QPushButton::clicked, this, &MainWindow::alarmMUp);
    connect(ui->b_alarm_h_down, &QPushButton::clicked, this, &MainWindow::alarmHDown);
    connect(ui->b_alarm_m_down, &QPushButton::clicked, this, &MainWindow::alarmMDown);
    connect(ui->b_save_alarm, &QPushButton::clicked, this, &MainWindow::saveAlarm);
    connect(ui->b_cancel_alarm, &QPushButton::clicked, this, &MainWindow::cancelAlarmEdit);
    connect(AlarmControllerObject, &AlarmController::openWindow, this, &MainWindow::openTriggeredAlarmWindow);
    connect(ui->b_sound_alarm, &QPushButton::clicked, this, &MainWindow::loadSound);   
}
