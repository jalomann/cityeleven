#ifndef COUNTRYLINE2_H
#define COUNTRYLINE2_H

#include <QGraphicsLineItem>

class CountryLine2 : public QGraphicsLineItem
{
public:
    CountryLine2(qreal x1, qreal y1, qreal x2, qreal y2);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget);


};

#endif // COUNTRYLINE2_H
