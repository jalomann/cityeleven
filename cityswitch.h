#ifndef CITYSWITCH_H
#define CITYSWITCH_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QGraphicsLineItem>

class QGradient;

class CitySwitch : public QGraphicsItem
{
public:
    enum Kind { Park, Hall, Tower };

    CitySwitch(Kind kind);

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool Pressed;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int kind;
    int colorid;
    QColor color;
    QColor symboltextcolor;
    QPainterPath shape;

};

#endif
