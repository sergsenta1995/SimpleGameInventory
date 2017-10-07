#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

class Server : public QTcpServer {
    Q_OBJECT

public:
    explicit Server(int port);

private:
    quint16     nextBlockSize;

public slots:
    void slotNewConnection();
    void slotReadClient();

signals:
    void acceptedInventoryToInventoryData(int dropRow, int dropColumn, int dropValue, int dragRow, int dragColumn);
    void acceptedObjectToInventoryData(int dropRow, int dropColumn, int dropValue);
};

#endif // SERVER_HPP
