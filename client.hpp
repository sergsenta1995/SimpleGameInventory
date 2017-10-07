#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QTcpSocket>
#include <QDataStream>

class Client : public QTcpSocket {
    Q_OBJECT
public:
    Client(const QString& host, int port);

private:
    quint16 nextBlockSize;

public:
    void slotSendToServer(int dropRow, int dropColumn, int dropValue);
    void slotSendToServer(int dropRow, int dropColumn, int dropValue, int dragRow, int dragColumn);

private slots:
    void slotError(QAbstractSocket::SocketError err);
};

#endif // CLIENT_HPP
