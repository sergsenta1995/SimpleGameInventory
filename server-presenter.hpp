#ifndef SERVERPRESENTER_HPP
#define SERVERPRESENTER_HPP

#include "abstract-presenter.hpp"
#include "server.hpp"

class ServerPresenter : public AbstractPresenter {
    Q_OBJECT

public:
    ServerPresenter(InventoryWidget *widget);

private:
    Server *server;

public slots:
    void slotApplyData(int row, int column, int value, const QString &picture);
};

#endif // SERVERPRESENTER_HPP
