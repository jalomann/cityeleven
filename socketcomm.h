#ifndef SOCKETCOMM_H
#define SOCKETCOMM_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class SocketComm : public QObject
{
    Q_OBJECT
public:
    explicit SocketComm(QObject *parent = 0);
    void Connect(QString &cml);

signals:
    
public slots:

private:
    QTcpSocket *socket;
    
};

#endif // SOCKETCOMM_H
