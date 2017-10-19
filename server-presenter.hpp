#ifndef SERVER_PRESENTER_HPP
#define SERVER_PRESENTER_HPP

#include "abstract-presenter.hpp"
#include "server.hpp"

/*!
 * \brief Серверное представление.
 * \details Отвечает за взаимодействие между View <-> Server
 */
class ServerPresenter : public AbstractPresenter {
    Q_OBJECT

public:
    ServerPresenter(InventoryWidget *widget);

private:
    Server *server;

public slots:
    void slotApplyData(int row, int column, int value, const QString &picture);
};

#endif // SERVER_PRESENTER_HPP
