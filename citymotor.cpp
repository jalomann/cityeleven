#include <QtGui>
#include <QtWidgets>
#include <cmath>
#include <iostream>

#include "cityscape.h"
#include "citymotor.h"
#include "motordialog.h"
#include "socketcomm.h"

CityMotor::CityMotor(Kind kind)
{
    this->kind = kind;
    temperature = 12;

    int green = 96 + (std::rand() % 64);
    int red = 16 + green + (std::rand() % 64);
    int blue = 16 + (std::rand() % green);
    color = QColor(red, green, blue);
    symboltextcolor = QColor(Qt::white);

        color = QColor(192 + (std::rand() % 32), 255,
                       192 + (std::rand() % 16));
        int a = (std::rand() % 6) + 10;
        int b = (std::rand() % 6) + 10;
        QPolygonF block;
        QPolygonF bloc2;
        block << QPointF(-5, -a) << QPointF(-5, -5) << QPointF(-10, -5)
              << QPointF(-10, 5) << QPointF(-5, 5)  << QPointF(-5, 10)
              << QPointF(5, 10)  << QPointF(5, 5)   << QPointF(b, 5)
              << QPointF(b, -5)  << QPointF(5, -5)  << QPointF(5, -a);

        bloc2 << QPointF(15, 15) << QPointF(20, 20) << QPointF(20, 25)
              << QPointF(20, 30) << QPointF(15, 25)  << QPointF(10, 30)
              << QPointF(10, 25)  << QPointF(10, 20)   << QPointF(15, 15);

        int padding1 = (std::rand() % 8) + 2;
        int padding2 = (std::rand() % 8) + 2;
        // shape.addRect(boundingRect().adjusted(+padding1, +padding1, -padding2, -padding2));
        shape.addRect(boundingRect());

        int w1 = (std::rand() % 10) + 8;
        int h1 = (std::rand() % 28) + 8;
        int w2 = (std::rand() % 10) + 8;
        int h2 = (std::rand() % 24) + 8;
        //setFlag(ItemIsMovable);

        // text added
        font = qApp->font();
        font.setBold(true);
        dialog = new MotorDialog;

}

QRectF CityMotor::boundingRect() const
{
    return QRectF(-20, -20, 140, 40);
}

void CityMotor::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget * /* widget */)
{
    QRectF rec = boundingRect();
    QPen pen(Qt::black);
    pen.setWidth(3);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);
    int zoom = 3;
    temperature++;

    //if (option->levelOfDetail < 4.0)
    if (zoom < 4.0) {
        if(Pressed)
        {
            //color = QColor(192, 255, 192);

        }
        else
        {
            //color = QColor(112, 215, 192);
        }

        painter->drawRect(boundingRect());
        painter->fillPath(shape, color);

        pen.setWidth(2);
        if(Pressed)
        {
            pen.setColor(symboltextcolor);
            painter->setPen(pen);
        }
        else
        {
            pen.setColor(Qt::white);
            painter->setPen(pen);
        }
        pen.setColor(symboltextcolor);

        pen.setWidth(3);
        painter->setPen(pen);

        // draw motor symbol. circle first and then M
        painter->drawEllipse(-10,10,20,-20);
        painter->drawLine(-5, 5, -5,-5);
        painter->drawLine(-5,-5, 0,1);
        painter->drawLine(  0, 1, 5,-5);
        painter->drawLine( 5, -5, 5,5);

        // text added
        pen.setColor(Qt::black);
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawText(50,0,QString("Motor x"));
        //font.setBold(false);

        // jkoi add dynamic number
        QString temperatureStr;
        temperatureStr.setNum(temperature);
        painter->drawText(50,10,QString(temperatureStr));
        // jkoi add one single point
        painter->drawPoint(-15,-15);

        std::cout << "CityMotor  paint Upper IF ... " << zoom << "\n";

    } else {
        QLinearGradient gradient(QPoint(-20, -20), QPoint(+20, +20));
        int coeff = 105 + int(std::log(option->levelOfDetail - 4.0));
        gradient.setColorAt(0.0, color.lighter(coeff));
        gradient.setColorAt(1.0, color.darker(coeff));
        painter->fillPath(shape, gradient);
        std::cout << "CityMotor  paint Lower IF ... " << zoom << "\n";
    }
}
void CityMotor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (Pressed){
        Pressed = false;
    } else {
        Pressed = true;
    }

    colorid++;
    if (colorid>6){
        colorid=0;
    }

    switch (colorid) {
    case 0:
        // grey
        color = QColor(184, 184, 184);
        // black
        symboltextcolor = QColor(0, 0, 0);
        break;
    case 1:
        // white
        color = QColor(250, 250, 250);
        // black
        symboltextcolor = QColor(0, 0, 0);
        break;
    case 2:
        // green
        color = QColor(0, 255, 0);
        // black
        symboltextcolor = QColor(0, 0, 0);
        //cline = QString("motor1;1;start;1");
        //sendCommand(cline);
        break;
    case 3:
        // yellow
        color = QColor(255, 255, 127);
        // black
        symboltextcolor = QColor(0, 0, 0);

        showDialog();
        break;
    case 4:
        // red
        color = QColor(255, 0, 0);
        // black
        symboltextcolor = QColor(0, 0, 0);
        break;
    case 5:
        // violet
        color = QColor(255, 0, 255);
        // white
        symboltextcolor = QColor(255, 255, 255);
        break;
    case 6:
        // blue
        color = QColor(0, 0, 255);
        // white
        symboltextcolor = QColor(255, 255, 255);
        cline = QString("motor1;1;stop;0");
        sendCommand(cline);
        break;
    default:
        break;
    }
    std::cout << "CityMotor  colorid .......... " << colorid << "\n";
    //std::cout << "Command ...................... " << cline << "\n";

    //Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);

}

void CityMotor::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //Pressed = false;

    update();
    QGraphicsItem::mouseReleaseEvent(event);

}

void CityMotor::setText(QString &text)
{
    prepareGeometryChange();
    str = text;
    update();

}

void CityMotor::showDialog()
{
    //dialog->show();
    //QPoint  mainWinPos = Cityscape::button1->pos();
    QPointF motorBlockPos = this->pos();
    //int w = this->width();
    std::cout << "Motor block pos X ... : " << motorBlockPos.x() << "\n" ;
    std::cout << "Motor block pos Y ... : " << motorBlockPos.y() << "\n" ;

    //QPoint motorDialogPos = this->pos();
    //std::cout << "Button 5 pos Y .. : " << motorDialogPos.y() << "\n" ;
    //std::cout << "Button 5 pos X .. : " << motorDialogPos.x() << "\n" ;

    // x,y
    QPoint mainWinPos = parentpointter->pos(); // get the position
    //dialog->move(motorBlockPos.x()+250,motorBlockPos.y());

    dialog->move(parentpointter->pos().x()+(parentpointter->width()/2) , parentpointter->pos().y()+(parentpointter->height()/2) );
    dialog->show();

}

void CityMotor::slotMainWinPos(QPoint &mpos)
{
    mWinPos = mpos;
}

QString CityMotor::text() const
{
    return str;
}
void CityMotor::sendCommand(QString &commandline){
    mSocket = new SocketComm();
    mSocket->Connect(commandline);

}
