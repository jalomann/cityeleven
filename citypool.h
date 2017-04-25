#ifndef CITYPOOL_H
#define CITYPOOL_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QGraphicsLineItem>

class QGradient;

class CityPool : public QGraphicsItem
{
public:
    enum Kind { Vertical, Horizontal };

    CityPool(Kind kind);

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
