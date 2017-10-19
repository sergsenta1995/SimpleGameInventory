#include "client-presenter.hpp"

ClientPresenter::ClientPresenter(InventoryWidget *widget) :
    AbstractPresenter(widget)
{    
    client = new Client("localhost", 2323);

    connect(view, &InventoryWidget::changeCellData, this, &ClientPresenter::onUpdateCell);
    view->init(model->getContent());
}

void ClientPresenter::onUpdateCell(int row, int column, int value, const QString &picture)
{
    model->update(row, column, value, picture);
    client->sendToServer(row, column, value, picture);
}
