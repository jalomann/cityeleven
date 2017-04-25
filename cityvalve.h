#ifndef CITYVALVE_H
#define CITYVALVE_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QGraphicsLineItem>

class QGradient;

class CityValve : public QGraphicsItem
{
public:
    // Auma is registered trademark of Auma
    // Sipos is registered trademark of Siemens
    enum Kind { Auma, Sipos };

    CityValve(Kind kind);

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
