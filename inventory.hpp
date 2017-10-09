#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QTableWidget>
#include "inventory-facade.hpp"

class InventoryFacade;

class Inventory : public QTableWidget {
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);

protected:
    InventoryFacade *facade;
};

#endif // INVENTORY_HPP
