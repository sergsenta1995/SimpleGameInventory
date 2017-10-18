#include "inventory-facade.hpp"
#include <QSqlQuery>
#include <QDebug>

InventoryFacade::InventoryFacade()
{
}

void InventoryFacade::init(Inventory &inventory)
{
    QSqlQuery query;
    // NOTE: По умочлчанию первый инвентарь,
    //       т. к. возможноть выбора ивентаря не предусматривалась.
    query.prepare("SELECT dimension "
                  "FROM inventory "
                  "WHERE id = 1");
    query.exec();
    query.next();
    int size = query.value(0).toInt();    
    query.clear();
    inventory.setupSize(size);

    query.prepare("SELECT row, column, count_objects, type, picture "
                  "FROM inventory_content, game_object "
                  "WHERE id_inventory = ? and "
                  "game_object.id = inventory_content.id_object");
    // NOTE: По умочлчанию первый инвентарь,
    //       т. к. возможноть выбора ивентаря не предусматривалась.
    query.addBindValue(1);
    query.exec();

    while (query.next())
    {
        int row = query.value("row").toInt();
        int column = query.value("column").toInt();
        int value = query.value("count_objects").toInt();
        inventory.setValue(row, column, value);
    }

    query.clear();
    query.prepare("SELECT * "
                  "FROM inventory "
                  "WHERE id = ? ");
    // NOTE: По умочлчанию первый инвентарь,
    //       т. к. возможноть выбора ивентаря не предусматривалась.
    query.addBindValue(1);
    query.exec();
    query.next();
    //int dimension = query.value("dimension").toInt();
    //inventory.setRowCount(dimension);
}

void InventoryFacade::update(int row, int column, int value)
{
    QSqlQuery query;

    if (value == 0)
    {
        query.prepare("DELETE FROM inventory_content "
                      "WHERE id_inventory = :id_inventory and "
                      "      row = :row and "
                      "      column = :column");
        query.bindValue(":id_inventory", 1);
        query.bindValue(":row", row);
        query.bindValue(":column", column);
        query.exec();

        return;
    }    

    query.prepare("INSERT OR REPLACE INTO inventory_content "
                  "VALUES (null, :id, :row, :column, 1, :count_objects);");
    query.bindValue(":id", 1);
    query.bindValue(":row", row);
    query.bindValue(":column", column);
    query.bindValue(":count_objects", value);
    query.exec();
}
