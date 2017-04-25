#include <QtGui>
#include <QtWidgets>
#include <iostream>
#include <QPen>

#include "annotation.h"
#include "cityblock.h"
#include "cityscape.h"
#include "cityview.h"
#include "cityvalve.h"
#include "citymotor.h"
#include "citypool.h"
#include "citypump.h"
#include "cityline1.h"
#include "cityswitch.h"
#include "spreadsheet.h"
#include "countryline1.h"
#include "countryline2.h"
#include "motordialog.h"
#include "socketcomm.h" // sss add socket step1

Cityscape::Cityscape()
{
    scene = new QGraphicsScene(-22.25, -22.25, 980, 800);
    scene->setBackgroundBrush(QColor(255, 255, 238));
    generateCityBlocks();

    view = new CityView;
    view->setScene(scene);

    button1 = new QPushButton(tr("Start pool"));
    button2 = new QPushButton(tr("Stop pool"));
    button3 = new QPushButton(tr("Update text"));
    button4 = new QPushButton(tr("Button 4"));
    button5 = new QPushButton(tr("Motor"));
    button6 = new QPushButton(tr("Telegram"));
    button7 = new QPushButton(tr("Button 7"));
    button8 = new QPushButton(tr("Button 8"));
    button9 = new QPushButton(tr("C&lose"));

    button1->setMinimumHeight(90);
    button2->setMinimumHeight(90);
    button9->setMinimumHeight(90);
    QPixmap pixmap(":/images/motor.png");
    QIcon ButtonIcon(pixmap);
    button5->setIcon(ButtonIcon);
    button5->setIconSize(pixmap.rect().size());

    connect(button1, SIGNAL(clicked()),this,SLOT(button1startTimer()));
    connect(button2, SIGNAL(clicked()),this,SLOT(button2stopTimer()));
    connect(button3, SIGNAL(clicked()),this,SLOT(button3talkToText()));
    connect(button9, SIGNAL(clicked()),this,SLOT(close()));

    device = QString("motor");
    devnum = QString("1");
    command = QString("setpoint");
    //command = QString("start");
    value = QString("85");
    //commandline = device.toLatin1();
    commandline = device.toLatin1() + ";" + devnum.toLatin1() + ";" + command.toLatin1() + ";" + value.toLatin1();

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(button1);
    leftLayout->addWidget(button2);
    leftLayout->addWidget(button3);
    leftLayout->addWidget(button4);
    leftLayout->addWidget(button5);
    leftLayout->addWidget(button6);
    leftLayout->addWidget(button7);
    leftLayout->addWidget(button8);
    leftLayout->addWidget(button9);
    leftLayout->addStretch();

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->setSizeConstraint(QLayout::SetFixedSize); // xxx20150406
    spreadsheet = new Spreadsheet;

    rightLayout->addWidget(view);
    rightLayout->addWidget(spreadsheet);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
    //setCentralWidget(mainLayout);
    setWindowTitle(tr("Cityvalve Eleven"));

    // initialize pool level. otherwise it goes out of range
    level=0;
    leveldir=0;

    QPoint mainWinPosX = this->pos();
    std::cout << "Main Window X ... : " << mainWinPosX.x() << "\n" ;

    dialog = new MotorDialog;
    //dialog->move(100,700);
    connect(button5, SIGNAL(clicked()),this,SLOT(button5showDialog()));

    //cTest->Connect();
    connect(button6, SIGNAL(clicked()),this,SLOT(button6connect()));

}

void Cityscape::generateCityBlocks()
{
            CityValve::Kind kind21;
            CityMotor::Kind kind41;
            CityPool::Kind kind31;
            CitySwitch::Kind kind61;
            CityPump::Kind kind71;

            QString name07;
            QString name08;
            QString name09;
            QString name10;

            QString name21;

            //bool major = (std::rand() % 10 == 0);
            bool major = (1);
            std::cout << "major .... : " << major << "\n" ;

            Annotation *annotation01 = new Annotation("Switch 1", major);
            // example how to export position from the block03
            // annotation03->setPos(block03->pos());
            annotation01->setPos(40, 40);
            scene->addItem(annotation01);


            Annotation *annotation02 = new Annotation("Switch 3", major);
            annotation02->setPos(320,140);
            scene->addItem(annotation02);

            // Annotation *annotation03 = new Annotation(name03.arg(i.next()), major);
            Annotation *annotation03 = new Annotation("Switch 2", major);
            // annotation03->setPos(block03->pos());
            annotation03->setPos(40,140);
            scene->addItem(annotation03);

            annotionpublic = new Annotation("Flow", major);
            annotionpublic->setPos(200,410);
            scene->addItem(annotionpublic);

            // changes the previous text. I need only the pointer to the annotation
            annotionpublic = annotation03;

            CityValve *block21 = new CityValve(kind21);
            block21->setPos(QPointF( 640, 425));
            scene->addItem(block21);

            CityMotor *block41 = new CityMotor(kind41);
            block41->setPos(QPointF(  50, 520));
            block41->parentpointter = this; // ppp parentpointer is needed to communicate to socket step2
            scene->addItem(block41);

            // pool
            block32 = new CityPool(kind31);
            block32->setPos(QPointF( 500, 410));
            scene->addItem(block32);

            // big tank
            block33 = new CityPool(kind31);
            block33->setPos(QPointF( 300, 610));
            scene->addItem(block33);

            CityLine1 *line51 = new CityLine1();
            line51->setPos(QPointF(340,690));
            //scene->addItem(line51);

            CitySwitch *block61 = new CitySwitch(kind61);
            block61->setPos(QPointF(150, 30));
            scene->addItem(block61);

            CitySwitch *block62 = new CitySwitch(kind61);
            block62->setPos(QPointF(150, 140));
            scene->addItem(block62);

            CitySwitch *block63 = new CitySwitch(kind61);
            block63->setPos(QPointF(450, 140));
            scene->addItem(block63);

            CityPump *block71 = new CityPump(kind71);
            block71->setPos(QPointF(250,518));
            scene->addItem(block71);

            QPen pipeline1(Qt::black);
            pipeline1.setWidth(3);
            // horizontal lines
            scene->addLine( 20, 60,950, 60, pipeline1);
            scene->addLine( 20,280,200,280, pipeline1);
            scene->addLine(420,280,950,280, pipeline1);

            // vertical motor
            scene->addLine( 50,285, 50,495, pipeline1);
            // from tank to pool
            // intake from the big tank
            scene->addLine(300,640,300,660, pipeline1);
            scene->addLine(250,660,300,660, pipeline1);
            scene->addLine(250,540,250,660, pipeline1);
            scene->addLine(250,355,250,495, pipeline1);
            scene->addLine(250,355,500,355, pipeline1);
            scene->addLine(500,355,500,380, pipeline1);

            // pool outlet
            scene->addLine(525,425,610,425, pipeline1);
            scene->addLine(670,425,730,425, pipeline1);
            scene->addLine(730,425,730,525, pipeline1);
            scene->addLine(730,525,300,525, pipeline1);
            scene->addLine(300,525,300,570, pipeline1);

            // second bar
            scene->addLine(640,280,640,380, pipeline1);

            // vertical switch 2
            scene->addLine(150, 60,150,105, pipeline1);
            scene->addLine(150,175,150,280, pipeline1);

            // vertical switch 3
            scene->addLine(450, 60,450,105, pipeline1);
            scene->addLine(450,175,450,280, pipeline1);


#if 0
            // sets the settings that are in creator. This is CountryLine 1
            CountryLine1 *couline1 = new CountryLine1();
            scene->addItem(couline1);

            // if you change the the line setting they are set after creation
            CountryLine1 *couline2 = new CountryLine1();
            couline1->setLine(610,12,850,12);
            //couline1->setPen(pipeline1);
            couline1->setPen(QColor(Qt::red));
            scene->addItem(couline2);

            // totally independent with position in creator
            CountryLine2 *couline3 = new CountryLine2(610,22,850,22);
            //couline1->setLine(210,12,450,12);
            //couline1->setPen(pipeline1);
            couline3->setPen(QColor(Qt::blue));
            scene->addItem(couline3);
#endif


}

void Cityscape::timerEvent(QTimerEvent *event){
    // std::cout << "timer event... : " << "\n" ;
    if (event->timerId()==myTimerId){

            if (leveldir == 1){
                level++;
            }

            if (leveldir == 0)
            {
                level--;
            }
            if (level > 18)
            {
                leveldir = 0;
            }
            if (level < -18)
            {
                leveldir = 1;
            }
            // std::cout << "timer event - level ... : " << level << "\n";

            // setFormula (x,y) cell
            spreadsheet->setFormula(0,0,QString::number(level));

            block32->setLevel(level);
            block32->update();
            block33->setLevel(level * -1);
            block33->update();

     }
 #if 0
    if (event->timerId()==processTimerId){
        std::cout << "process timer " << "\n";
        //processIndex++;
    }
#endif
}
#if 0
void Cityscape::sigMainWinPos(const QPoint &mpos)
{
    mainWinPos = this->pos();
    return mainWinPos;
}
#endif

void Cityscape::button1startTimer()
{
    std::cout << "button 1 pressed - start timer ... : " << "\n" ;
    myTimerId = startTimer(200);
    processTimerId = startTimer(800);
}

void Cityscape::button2stopTimer()
{
    std::cout << "button 2 pressed - stop timer .... : " << "\n" ;
    killTimer(myTimerId);
    myTimerId=0;

}
void Cityscape::button3talkToText()
{
    std::cout << "button 3 talk to text .... : " << "\n" ;
    annotionpublic->setText("Jarmo <date> 4.6.2015");
    spreadsheet->setFormula(0,0,QString::number(level));
    spreadsheet->text(1,1);
    int col = spreadsheet->currentColumn();

    //xxx
    std::cout << col << "\n";
}

void Cityscape::button5showDialog()
{
    dialog->show();
    mainWinPos = this->pos();
    emit sigMainWinPos(mainWinPos);

    QPoint mainWindowPos = this->pos();
    int w = this->width();
    //std::cout << "Main Window X ... : " << mainWindowPos.x() << "\n";
    //std::cout << "Main Window X ... : " << w << "\n";

    QPoint button5pos = button5->pos();
    std::cout << "Button 5 pos Y .. : " << button5pos.y() << "\n" ;
    std::cout << "Button 5 pos X .. : " << button5pos.x() << "\n" ;

    // x,y
    dialog->move(mainWindowPos.x()+w-dialog->width(),button5pos.y());

}

//void Cityscape::button6connect(QString &device)
void Cityscape::button6connect()
{
    QString telo = QString("Motore;1;start;3");
    telo = commandline;
    cTest = new SocketComm(); // sss add socket step1
    cTest->Connect(telo); // sss add socket step1
}
