 #include "inventory-presenter.hpp"
#include "client-inventory.hpp"

InventoryPresenter::InventoryPresenter(Inventory *inventory, InventoryWidget *widget) :
    model(inventory),
    view(widget)
{
    connect(view, &InventoryWidget::changeCellData, this, &InventoryPresenter::onUpdateCell);
    view->init(model->getContent());
}

void InventoryPresenter::onUpdateCell(int row, int column, int value)
{
    model->update(row, column, value);
}
