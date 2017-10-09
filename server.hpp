#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

/*!
 * \brief Класс-сервер для принятия сообщений от клиента.
 * \details Принимает и устанавливает данные, принятые от клиента
 */
class Server : public QTcpServer {
    Q_OBJECT

public:
    explicit Server(int port);

private:
    quint16     nextBlockSize;

public slots:
    //! Создает новое соединение, подключает слоты обработки принимаемых данных.
    void slotNewConnection();
    //! Обрабатывает принимаемые данные.
    void slotReadClient();

signals:
    // Позволяет применить отправленные клиентом изменения в виджете.
    void applyData(const QVector<int> &sentData);
};

#endif // SERVER_HPP
