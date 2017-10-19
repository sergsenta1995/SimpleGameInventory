#ifndef CLIENT_PRESENTER_HPP
#define CLIENT_PRESENTER_HPP

#include "abstract-presenter.hpp"
#include "client.hpp"

class ClientPresenter : public AbstractPresenter {
    Q_OBJECT

public:
    ClientPresenter(InventoryWidget *widget);

private:
    Client          *client;

public slots:
    void onUpdateCell(int row, int column, int value, const QString &picture);

};

#endif // CLIENT_PRESENTER_HPP
