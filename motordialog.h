#ifndef MOTORDIALOG_H
#define MOTORDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "socketcomm.h" // sss add socket step2

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class MotorDialog : public QDialog
{
    Q_OBJECT

public:
    MotorDialog(QWidget *parent = 0);

signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void findClicked();
    void enableStopButton(const QString &text);
    void enableSetpointButton(const QString &text);
    void connectforcommand();
    void connectforstart();
    void connectforstop();
    void connectforinc();
    void connectfordec();

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QCheckBox *testCheckBox;
    QPushButton *stopButton;
    QPushButton *startButton;
    QPushButton *setpointButton;
    QPushButton *incButton;
    QPushButton *decButton;
    QPushButton *closeButton;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QLabel *statusLabel;

    QString device;
    QString devnum;
    QString command;
    QString value;
    SocketComm *mSocket; // sss add socket step2
    QByteArray commandline;

};

#endif
