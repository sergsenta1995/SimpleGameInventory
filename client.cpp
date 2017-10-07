#include "client.hpp"

Client::Client(const QString& host, int port):
    nextBlockSize(0)
{
    connectToHost(host, port);
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(errorString())
                    );
    qDebug() << strError;
}

void Client::slotSendToServer(int dropRow, int dropColumn, int dropValue)
{
    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    const int NUMBER_OF_ARGUMENTS = 3;
    out << quint16(0) << NUMBER_OF_ARGUMENTS << dropRow << dropColumn << dropValue;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    write(block);
}

void Client::slotSendToServer(int dropRow, int dropColumn, int dropValue, int dragRow, int dragColumn)
{
    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    const int NUMBER_OF_ARGUMENTS = 5;
    out << quint16(0) << NUMBER_OF_ARGUMENTS << dropRow << dropColumn << dropValue << dragRow << dragColumn;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    write(block);
}

