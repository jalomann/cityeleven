#include <QtGui>
#include <QtWidgets>
#include <cmath>
#include <iostream>

#include "citypool.h"

CityPool::CityPool(Kind kind)
{
    this->kind = kind;

    level = 1;
    leveldir = 0;

    int green = 96 + (std::rand() % 64);
    int red = 16 + green + (std::rand() % 64);
    int blue = 16 + (std::rand() % green);
    color = QColor(red, green, blue);

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
    //  shape.addPolygon(block);

        bloc2 << QPointF(15, 15) << QPointF(20, 20) << QPointF(20, 25)
              << QPointF(20, 30) << QPointF(15, 25)  << QPointF(10, 30)
              << QPointF(10, 25)  << QPointF(10, 20)   << QPointF(15, 15);
    //        shape.addPolygon(bloc2);
    //        shape.lineTo(100,200);

        int padding1 = (std::rand() % 8) + 2;
        int padding2 = (std::rand() % 8) + 2;
        // shape.addRect(boundingRect().adjusted(+padding1, +padding1,-padding2, -padding2));
        shape.addRect(boundingRect());

        int w1 = (std::rand() % 10) + 8;
        int h1 = (std::rand() % 28) + 8;
        int w2 = (std::rand() % 10) + 8;
        int h2 = (std::rand() % 24) + 8;
        //setFlag(ItemIsMovable);
}

void CityPool::setLevel(int l)
{
    level = l;
    // std::cout << "CityPool  set     Level ......  " << level << "\n";
}

QRectF CityPool::boundingRect() const
{
    return QRectF(-20, -20, 40, 40);
}

void CityPool::paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget * /* widget */)
{
    QRectF rec = boundingRect();
    QPen pen(Qt::black);
    pen.setWidth(3);
    painter->setPen(pen);
    int zoom = 3;
    int lowerlevel = 0;
    int lines = 0;

    //if (option->levelOfDetail < 4.0)
    if (zoom < 4.0) {
        painter->drawRect(boundingRect());
        painter->fillPath(shape, color);

        pen.setWidth(2);
        pen.setColor(Qt::blue);
        painter->setPen(pen);

        //std::cout << "CityPool   paint Level .......  " << level << "\n";
        painter->drawLine(-19, level, 19, level );

        for ( lines = level ; lines<20 ; lines++ ){
                painter->drawLine(-19, lines, 19, lines );
        }

        // std::cout << "CityPool   paint Level .......  " << level << "\n";

    } else {
        QLinearGradient gradient(QPoint(-20, -20), QPoint(+20, +20));
        int coeff = 105 + int(std::log(option->levelOfDetail - 4.0));
        gradient.setColorAt(0.0, color.lighter(coeff));
        gradient.setColorAt(1.0, color.darker(coeff));
        // painter->fillPath(shape, gradient);
        // std::cout << "CityPool - Lower IF ... \n";
    }
}
