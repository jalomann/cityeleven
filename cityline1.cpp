#include <QtGui>
#include <QtWidgets>
#include <cmath>
#include <iostream>

#include "cityline1.h"

CityLine1::CityLine1()
{
    level = 1;
    leveldir = 0;

    int green = 96 + (std::rand() % 64);
    int red = 16 + green + (std::rand() % 64);
    int blue = 16 + (std::rand() % green);
    color = QColor(red, green, blue);

        color = QColor(192 + (std::rand() % 32), 255,
                       192 + (std::rand() % 16));
        setFlag(ItemIsMovable);
}

void CityLine1::setLevel(int l)
{
    level = l;
}

QRectF CityLine1::boundingRect() const
{
     return QRectF(-110, -5, 140, 10);
}

void CityLine1::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget * /* widget */)
{
    QRectF rec = boundingRect();
    QPen pen(Qt::black);
    pen.setWidth(1);
    painter->setPen(pen);

        painter->drawRect(boundingRect());
        //painter->fillPath(shape, color);

        pen.setWidth(2);
        pen.setColor(Qt::red);
        painter->setPen(pen);

        painter->drawLine(-100, 0, 15, 0);
        std::cout << "CityLine   Line1 ............ " << level << "\n";

}
