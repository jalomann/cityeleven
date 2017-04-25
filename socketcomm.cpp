#include "socketcomm.h"
#include <unistd.h>

SocketComm::SocketComm(QObject *parent) :
    QObject(parent)
{
}

void SocketComm::Connect(QString &cml)
{
    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.1.5", 9067);

    if(socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        // send
        QByteArray comu = cml.toLatin1();
        // S.Gaist's example to get number
        // QByteArray cmd = "something" + QByteArray::number(currentValue);
        qDebug() << "commandline ... " << qPrintable(comu) << "\n";
        // socket->write("motor;1;start;1");
        socket->write(qPrintable(comu));
        //socket->waitForBytesWritten(1000);
        socket->waitForConnected(1000);
        // usleep (1000000);

        socket->waitForReadyRead(300);
        qDebug() << "Reading: " << socket->bytesAvailable();

        qDebug() << socket->readAll();

        socket->close();
    } else {
        qDebug() << "Not connected!";
    }

    // sent

    // got

    // closed
}
