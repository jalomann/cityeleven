#ifndef CITYPUMP_H
#define CITYPUMP_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QGraphicsLineItem>

class QGradient;

class CityPump : public QGraphicsItem
{
public:
    enum Kind { Left, Up, Right, Down };

    CityPump(Kind kind);

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
