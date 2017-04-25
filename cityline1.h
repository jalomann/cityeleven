#ifndef CITYLINE1_H
#define CITYLINE1_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QGraphicsLineItem>

class QGradient;

class CityLine1 : public QGraphicsItem
{
public:

    CityLine1();

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setLevel(int l);
private:
    int kind;
    int level;
    int leveldir;
    QColor color;
    QPainterPath shape;

};

#endif
