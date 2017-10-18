#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QTableWidget>
#include "inventory-facade.hpp"

class InventoryFacade;

class Inventory : QObject{
    Q_OBJECT

public:
    explicit Inventory();
    void update(int row, int column, int value);
    void setValue(int row, int column, int value);
    void setupSize(int dimension);
    QVector<QVector<int>> getContent();

protected:
    InventoryFacade *facade;
    QVector<QVector<int>> content;
};

#endif // INVENTORY_HPP
