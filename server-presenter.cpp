#include "server-presenter.hpp"

ServerPresenter::ServerPresenter(InventoryWidget *widget) :
    AbstractPresenter(widget)
{
    server = new Server(2323);

    view->init(model->getContent());

    connect(server, &Server::applyData, this, slotApplyData);

}

void ServerPresenter::slotApplyData(int row, int column, int value, const QString &picture)
{
    view->rewriteItem(row, column, value, picture);
}
