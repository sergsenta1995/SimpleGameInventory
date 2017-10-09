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

void Client::sendToServer(const QVector<int> &sentData)
{
    QByteArray  block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_9);
    out << quint16(0) << sentData.size();
    foreach (int element, sentData) {
        out << element;
    }
    qDebug() << out;
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    write(block);
}
