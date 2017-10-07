#include "server-inventory.hpp"

ServerInventory::ServerInventory(QWidget *parent):
    Inventory(parent)
{
}

void ServerInventory::startServer()
{
    qDebug() << "server started";
    server = new Server(2323);

    connect(server, &Server::acceptedObjectToInventoryData, this, &ServerInventory::applyObjectToInventoryChange);
    connect(server, &Server::acceptedInventoryToInventoryData, this, &ServerInventory::applyInventoryToInventoryChange);

}

void ServerInventory::applyInventoryToInventoryChange(int dropRow, int dropColumn, int dropValue, int dragRow, int dragColumn)
{
    QTableWidgetItem *newItem = item(dropRow, dropColumn);
    if (newItem == nullptr)
    {
        newItem = new QTableWidgetItem;
        newItem->setText(QString::number(dropValue));
    }
    else
    {
        int oldValue = newItem->data(Qt::DisplayRole).toInt();
        newItem->setText(QString::number(oldValue + dropValue));
    }
    newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
    newItem->setBackground(QPixmap(":/images/red-apple.jpg").scaled(100, 100));
    //this->setItem(dragRow, dragColumn, nullptr);
    this->setItem(dropRow, dropColumn, newItem);
}

void ServerInventory::applyObjectToInventoryChange(int dropRow, int dropColumn, int dropValue)
{
    if (dropValue == 0)
    {
        qDebug() << dropRow << dropColumn;
        this->setItem(dropRow, dropColumn, nullptr);
        //this->removeCellWidget(dropRow, dropColumn);
        qDebug() << "&&&&&&&";
        return;
    }

    QTableWidgetItem *newItem = item(dropRow, dropColumn);
    if (newItem == nullptr)
    {
        newItem = new QTableWidgetItem;
        newItem->setText(QString::number(dropValue));
    }
    else
    {
        int oldValue = newItem->data(Qt::DisplayRole).toInt();
        newItem->setText(QString::number(oldValue + dropValue));
    }
    newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
    newItem->setBackground(QPixmap(":/images/red-apple.jpg").scaled(100, 100));
    this->setItem(dropRow, dropColumn, newItem);
}
