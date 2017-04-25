#include <QtWidgets>
#include "countryline1.h"

CountryLine1::CountryLine1()
{
    //myStart = start;
    //myEnd = end;
    setPen(QColor(Qt::green));
    setLine(610,1,850,1);
}

void CountryLine1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget)
{
    QPen pen(QColor(Qt::blue));
    painter->setPen(pen);

}
