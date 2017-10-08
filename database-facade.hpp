#ifndef DATABASEFACADE_HPP
#define DATABASEFACADE_HPP

#include "inventory.hpp"
#include <QSqlQuery>

class DatabaseFacade {
public:
    DatabaseFacade();
    void updateCell(int inventory_id, int row, int column, int value);
    void initInventory(Inventory &inventory_, int id = 1);

    Inventory *inventory;
};

#endif // DATABASEFACADE_HPP
