#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QTcpSocket>
#include <QDataStream>

class Client : public QTcpSocket {
public:
    Client(const QString& host, int port);

private:
    quint16 nextBlockSize;

public:
    void slotSendToServer(int row, int column, int value);

private slots:
    void slotError(QAbstractSocket::SocketError err);
};

#endif // CLIENT_HPP
