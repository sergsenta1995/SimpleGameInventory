#include "inventory-facade.hpp"
#include <QSqlQuery>
#include <QDebug>

InventoryFacade::InventoryFacade()
{
}

void InventoryFacade::init(Inventory &inventory)
{
    QSqlQuery query;
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
        QString value = query.value("count_objects").toString();
        QTableWidgetItem *newItem = new QTableWidgetItem(value);
        newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
        QString picture = query.value("picture").toString();
        QString type = query.value("type").toString();
        QStringList dataList = {type, picture};
        newItem->setBackground(QPixmap(picture).scaled(100, 100));
        newItem->setData(Qt::UserRole, dataList);
        inventory.setItem(row, column, newItem);
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
    int dimension = query.value("dimension").toInt();
    inventory.setRowCount(dimension);
}

void InventoryFacade::update(const QVector<int> &fieldsValue)
{
    qDebug() << "===========================";
    for (int i = 0; i < fieldsValue.size(); ++i)
        qDebug() << fieldsValue.at(i);
    QSqlQuery query;

    if (fieldsValue[3] == 0)
    {
        query.prepare("DELETE FROM inventory_content "
                      "WHERE id_inventory = ? and "
                      "      row = ? and "
                      "      column = ?");
        query.addBindValue(fieldsValue[0]);
        query.addBindValue(fieldsValue[1]);
        query.addBindValue(fieldsValue[2]);
        query.exec();
        return;
    }
    query.prepare("INSERT OR REPLACE INTO inventory_content "
                  "VALUES (null, ?, ?, ?, 1, ?);");
    query.addBindValue(fieldsValue[0]);
    query.addBindValue(fieldsValue[1]);
    query.addBindValue(fieldsValue[2]);
    query.addBindValue(fieldsValue[3]);
    if (query.exec() == false)
        qDebug() << "!!!!!!!!!";
}
