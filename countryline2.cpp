#include <QtWidgets>
#include "countryline2.h"

CountryLine2::CountryLine2(qreal x1, qreal y1, qreal x2, qreal y2)
{
    //myStart = start;
    //myEnd = end;

    setLine(x1,y1,x2,y2);
    setFlag(ItemIsMovable);

}

void CountryLine2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget)
{
    QPen pen(QColor(Qt::blue));
    painter->setPen(pen);

}
