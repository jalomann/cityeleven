#include <QtGui>
#include <QtWidgets>
#include <cmath>
#include <iostream>

#include "cityswitch.h"

CitySwitch::CitySwitch(Kind kind)
{
    this->kind = kind;

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
}

QRectF CitySwitch::boundingRect() const
{
    return QRectF(-20, -20, 40, 40);
}

void CitySwitch::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget * /* widget */)
{
    QRectF rec = boundingRect();
    QPen pen(Qt::black);
    pen.setWidth(3);
    painter->setPen(pen);
    int zoom = 3;

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

        if(colorid == 2)
        {
            painter->drawLine( 0, -17, 0, 17);

        }
        else
        {
            painter->drawLine( 0, -17, 0,-6);
            painter->drawLine(-8, -4,  0, 10);
            painter->drawLine(  0, 10,  0, 17);
        }
    }
}
void CitySwitch::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (Pressed){
        Pressed = false;
    }
    else{
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
        break;
    case 3:
        // yellow
        color = QColor(255, 255, 127);
        // black
        symboltextcolor = QColor(0, 0, 0);
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
        break;
    default:
        break;
    }
    std::cout << "CitySwitch colorid .......... " << colorid << "\n";

    //Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);

}

void CitySwitch::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);

}
