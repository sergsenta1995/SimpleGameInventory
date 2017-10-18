#ifndef INVENTORYPRESENTER_HPP
#define INVENTORYPRESENTER_HPP

#include "inventory.hpp"
#include "inventory-widget.hpp"

class InventoryPresenter : public QObject {
    Q_OBJECT

public:
    InventoryPresenter(Inventory *inventory, InventoryWidget *widget);

private:
    Inventory       *model;
    InventoryWidget *view;

public slots:
    void onUpdateCell(int row, int column, int value);

};

#endif // INVENTORYPRESENTER_HPP
