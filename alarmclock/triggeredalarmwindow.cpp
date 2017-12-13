#include "triggeredalarmwindow.h"

TriggeredAlarmWindow::TriggeredAlarmWindow(Alarm* obj, AlarmController* controller , QWidget *parent) :
    QWidget(parent),
    alarmObj(obj),
    AlarmControllerObject(controller)
{
    QSound* soundObj = new QSound(obj->getSoundFileName());
    AlarmControllerObject->setSoundObj(soundObj);
    AlarmControllerObject->startSound();

    this->setObjectName("triggeredAlarmWindow");
    this->setMaximumHeight(300);
    this->setMaximumWidth(450);

    QVBoxLayout* wLayout = new QVBoxLayout();
    QGroupBox* popupContext = new QGroupBox(this);
    QGridLayout* popupLayout = new QGridLayout();
    this->setLayout(wLayout);
    wLayout->addWidget(popupContext);
    popupContext->setLayout(popupLayout);

    QLabel* timeLabel = new QLabel(popupContext);
    popupLayout->addWidget(timeLabel, 1,2,1,1,Qt::AlignCenter);
    QFont timeFont( "Arial", 20, QFont::Bold);

    QString HString;
    QString MString;

    if(obj->getH() <= 9) HString = "0" + QString::number(obj->getH());
    else HString = QString::number(obj->getH());

    if(obj->getM() <= 9) MString = "0" + QString::number(obj->getM());
    else MString = QString::number(obj->getM());

    if(obj->getIsSnooth() == false) timeLabel->setText(HString + ':' + MString);
    else timeLabel->setText(HString + ':' + MString + " (Snooth)");
    timeLabel->setFont(timeFont);

    QPushButton* b_close = new QPushButton(popupContext);
    popupLayout->addWidget(b_close, 2,1,1,1);
    b_close->setText("Close");

    QPushButton* b_snooze = new QPushButton(popupContext);
    popupLayout->addWidget(b_snooze, 2,3,1,1);
    b_snooze->setText("Snooze");

    connect(b_close, &QPushButton::clicked, this, &TriggeredAlarmWindow::destroyThis);
    connect(b_snooze, &QPushButton::clicked, AlarmControllerObject, &AlarmController::addSnooth);
    connect(b_snooze, &QPushButton::clicked, this, &TriggeredAlarmWindow::destroyThis);

    this->show();
    //After 30sec window will destroy itself
    QTimer::singleShot(30000, this, destroyThis);
}

void TriggeredAlarmWindow::closeEvent(QCloseEvent *)
{
    AlarmControllerObject->stopSound();
}

void TriggeredAlarmWindow::destroyThis()
{
    AlarmControllerObject->stopSound();
    delete this;
}
