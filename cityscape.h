#ifndef CITYSCAPE_H
#define CITYSCAPE_H

#include <QDialog>
#include <QSet>
#include "citypool.h"
#include "annotation.h"
#include "spreadsheet.h"
#include "motordialog.h"
#include "socketcomm.h" // sss add socket step1

class QGraphicsScene;
class CityView;
class QPushButton;
class CityMotor; // ppp parentpointer is needed to communicate to socket step1

class Cityscape : public QDialog
{
    Q_OBJECT

public:
    Cityscape();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void button1startTimer();
    void button2stopTimer();
    void button3talkToText();
    void button5showDialog();
    void button6connect();

signals:
    void sigMainWinPos(QPoint &mpos);

private:
    void generateCityBlocks();
    QGraphicsScene *scene;
    CityView *view;
    Spreadsheet *spreadsheet;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button6;
    QPushButton *button7;
    QPushButton *button8;
    QPushButton *button9;
    int myTimerId;
    int processTimerId;
    int level;
    int leveldir;
    CityPool *block32;
    CityPool *block33;
    Annotation *annotionpublic;

    QString device;
    QString devnum;
    QString command;
    QString value;
    QByteArray commandline;

    CityMotor *motorpointer; // ppp parentpointer counterpart is needed to communicate to socket step2

    QPoint mainWinPos;
    MotorDialog *dialog;
    SocketComm *cTest; // sss add socket step1

};

#endif
