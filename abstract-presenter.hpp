#ifndef ABSTRACT_PRESENTER_HPP
#define ABSTRACT_PRESENTER_HPP

#include <QObject>
#include "inventory.hpp"
#include "inventory-widget.hpp"

class AbstractPresenter : public QObject {
    Q_OBJECT

public:
    explicit AbstractPresenter(InventoryWidget *widget,
                               QObject *parent = nullptr);

protected:
    InventoryWidget *view;
    Inventory       *model;
};

#endif // ABSTRACT_PRESENTER_HPP
