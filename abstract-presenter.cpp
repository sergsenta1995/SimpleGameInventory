#include "abstract-presenter.hpp"

AbstractPresenter::AbstractPresenter(InventoryWidget *widget,
                                      QObject *parent) :
    view(widget),
    model(new Inventory),
    QObject(parent)
{    
}
