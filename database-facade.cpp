#include "database-facade.hpp"
#include <QSqlDatabase>
#include <QDebug>
#include <QTableWidgetItem>

DatabaseFacade::DatabaseFacade()
{

}

void DatabaseFacade::updateCell(int inventory_id, int row, int column, int value)
{
    QSqlQuery query;

    if (value == 0)
    {
        qDebug() << inventory_id << row << column;
        query.prepare("DELETE FROM inventory_content "
                      "WHERE id_inventory = ? and "
                      "      row = ? and "
                      "      column = ?");
        query.addBindValue(inventory_id);
        query.addBindValue(row);
        query.addBindValue(column);
        if (query.exec() == false)
            qDebug() << "ooooh";
        return;
    }
    query.prepare("INSERT OR REPLACE INTO inventory_content "
                  "VALUES (null, ?, ?, ?, 1, ?);");
    query.addBindValue(inventory_id);
    query.addBindValue(row);
    query.addBindValue(column);
    query.addBindValue(value);
    query.exec();
}

void DatabaseFacade::initInventory(Inventory &inventory_, int id)
{
    QSqlQuery query;


    query.prepare("SELECT row, column, count_objects "
                  "FROM inventory_content "
                  "WHERE id_inventory = ?;");
    query.addBindValue(id);
    if (query.exec() == false)
        qDebug() << "fooo";

    while (query.next())
    {
        int row = query.value("row").toInt();
        int column = query.value("column").toInt();
        QString value = query.value("count_objects").toString();
        QTableWidgetItem *newItem = new QTableWidgetItem(value);
        newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
        newItem->setBackground(QPixmap(":/images/red-apple.jpg").scaled(100, 100));
        inventory_.setItem(row, column, newItem);
    }
}
