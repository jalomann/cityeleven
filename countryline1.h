#ifndef COUNTRYLINE1_H
#define COUNTRYLINE1_H

#include <QGraphicsLineItem>

class CountryLine1 : public QGraphicsLineItem
{
public:
    CountryLine1();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget);

};

#endif // COUNTRYLINE1_H
