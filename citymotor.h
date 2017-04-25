#ifndef CITYMOTOR_H
#define CITYMOTOR_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QGraphicsLineItem>
#include "motordialog.h"
#include "socketcomm.h"
#include "cityscape.h"

class QGradient;

class CityMotor : public QGraphicsItem
{
public:
    enum Kind { Big, Small, DC };

    CityMotor(Kind kind);

    QRectF boundingRect() const;
    Cityscape *parentpointter; // ppp parentpointer is needed to communicate to socket step1

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool Pressed;

    void setText(QString &text);
    void sendCommand(QString &commandline);
    QString text() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void showDialog();
    void slotMainWinPos(QPoint &mpos);

private:
    int kind;
    int colorid;
    int temperature;
    QColor color;
    QColor symboltextcolor;
    QPainterPath shape;

    QPoint mWinPos;
    Cityscape *citypos;

    QFont font;
    QString cline;
    QString str;
    MotorDialog *dialog;
    SocketComm *mSocket;

};

#endif
