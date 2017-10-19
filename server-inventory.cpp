#include "server-inventory.hpp"

ServerInventory::ServerInventory(QWidget *parent):
    InventoryWidget(parent)
{
}

void ServerInventory::startServer()
{    
    //server = new Server(2323);

    //connect(server, &Server::applyData, this, slotApplyData);
}

void ServerInventory::rewriteItem(int dropRow, int dropColumn, int dropValue, const QString &picture)
{
    if (dropValue == 0)
    {
        this->setItem(dropRow, dropColumn, nullptr);
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
    newItem->setBackground(QPixmap(picture).scaled(100, 100));
    this->setItem(dropRow, dropColumn, newItem);
}
