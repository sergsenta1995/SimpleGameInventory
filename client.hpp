#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QTcpSocket>
#include <QDataStream>

/*!
 * \brief Класс-клиент отправки сообщений на сервер
 */
class Client : public QTcpSocket {
    Q_OBJECT
public:
    Client(const QString& host, int port);
    //! Отправляет сообщение на сервер.
    void sendToServer(const QVector<int> &sentData);

private:
    quint16 nextBlockSize;

private slots:
    void slotError(QAbstractSocket::SocketError err);
};

#endif // CLIENT_HPP
