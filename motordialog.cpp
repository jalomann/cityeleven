#include <QtGui>
#include <QtWidgets>

#include "motordialog.h"

MotorDialog::MotorDialog(QWidget *parent)
    : QDialog(parent)
{
    label = new QLabel(tr("&Setpoint"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    statusLabel = new QLabel(tr("ready"));

    caseCheckBox = new QCheckBox(tr("&Field control"));
    testCheckBox = new QCheckBox(tr("&Test"));
    backwardCheckBox = new QCheckBox(tr("&Manual"));

    stopButton = new QPushButton(tr("&Stop"));
    stopButton->setDefault(true);
    stopButton->setEnabled(true);

    startButton = new QPushButton(tr("Start"));
    closeButton = new QPushButton(tr("Close"));
    setpointButton = new QPushButton(tr("Setpoint"));
    setpointButton->setDefault(true);
    setpointButton->setEnabled(false);

    incButton = new QPushButton(tr("Inc"));
    decButton = new QPushButton(tr("Dec"));

    connect(lineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(enableSetpointButton(const QString &)));

    connect(setpointButton, SIGNAL(clicked()),
            this, SLOT(connectforcommand()));
    connect(startButton, SIGNAL(clicked()),
            this, SLOT(connectforstart()));
    connect(stopButton, SIGNAL(clicked()),
            this, SLOT(connectforstop()));

    connect(incButton, SIGNAL(clicked()),
                    this, SLOT(connectforinc()));
    connect(decButton, SIGNAL(clicked()),
                    this, SLOT(connectfordec()));

    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(close()));

    //QHBoxLayout *topLeftLayout = new QHBoxLayout;

    //QVBoxLayout *leftLayout = new QVBoxLayout;

    scene = new QGraphicsScene;
    view = new QGraphicsView;
    view->setScene(scene);
    QPixmap pixmapMotor(":/images/motor.png");
    QGraphicsPixmapItem *grItemMotor = new QGraphicsPixmapItem(pixmapMotor);
    scene->addItem(grItemMotor);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    QHBoxLayout *incdecLayout = new QHBoxLayout;

    incdecLayout->addWidget(decButton);
    incdecLayout->addWidget(incButton);

    rightLayout->addWidget(label);
    rightLayout->addWidget(lineEdit);

    rightLayout->addWidget(caseCheckBox);
    rightLayout->addWidget(testCheckBox);
    rightLayout->addWidget(backwardCheckBox);
    rightLayout->addWidget(view);
    rightLayout->addWidget(statusLabel);
    rightLayout->addWidget(stopButton);
    rightLayout->addWidget(startButton);
    rightLayout->addWidget(setpointButton);
    rightLayout->addLayout(incdecLayout);

    rightLayout->addWidget(closeButton);

    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    //mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Motor"));
    setFixedHeight(sizeHint().height());
    // move(300,600);
}

void MotorDialog::findClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs =
            caseCheckBox->isChecked() ? Qt::CaseSensitive
                                      : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void MotorDialog::enableStopButton(const QString &text)
{
    stopButton->setEnabled(!text.isEmpty());
}

void MotorDialog::enableSetpointButton(const QString &text)
{
    setpointButton->setEnabled(!text.isEmpty());
}

void MotorDialog::connectforcommand(){

    device = QString("motor");
    devnum = QString("1");
    command = QString("setpoint");
    // value = QString("85");
    value = lineEdit->text();
    //commandline = device.toLatin1();
    commandline = device.toLatin1() + ";" + devnum.toLatin1() + ";" + command.toLatin1() + ";" + value.toLatin1();

    QString cline = QString(commandline);
    mSocket = new SocketComm();
    mSocket->Connect(cline);

}

void MotorDialog::connectforstart(){

    device = QString("motor");
    devnum = QString("1");
    command = QString("start");
    value = QString("1");
    commandline = device.toLatin1() + ";" + devnum.toLatin1() + ";" + command.toLatin1() + ";" + value.toLatin1();

    QString cline = QString(commandline);
    mSocket = new SocketComm();
    mSocket->Connect(cline);
    statusLabel->setText("Running");

}
void MotorDialog::connectforstop(){

    device = QString("motor");
    devnum = QString("1");
    command = QString("stop");
    value = QString("0");
    commandline = device.toLatin1() + ";" + devnum.toLatin1() + ";" + command.toLatin1() + ";" + value.toLatin1();

    QString cline = QString(commandline);
    mSocket = new SocketComm();
    mSocket->Connect(cline);
    statusLabel->setText("Stopped");

}
void MotorDialog::connectforinc(){

    device = QString("motor");
    devnum = QString("1");
    command = QString("inc");
    value = QString("1");
    commandline = device.toLatin1() + ";" + devnum.toLatin1() + ";" + command.toLatin1() + ";" + value.toLatin1();

    QString cline = QString(commandline);
    mSocket = new SocketComm();
    mSocket->Connect(cline);

}
void MotorDialog::connectfordec(){

    device = QString("motor");
    devnum = QString("1");
    command = QString("dec");
    value = QString("1");
    commandline = device.toLatin1() + ";" + devnum.toLatin1() + ";" + command.toLatin1() + ";" + value.toLatin1();

    QString cline = QString(commandline);
    mSocket = new SocketComm();
    mSocket->Connect(cline);

}
