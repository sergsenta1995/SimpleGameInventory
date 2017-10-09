#include "server-inventory.hpp"

ServerInventory::ServerInventory(QWidget *parent):
    Inventory(parent)
{
}

void ServerInventory::startServer()
{
    qDebug() << "server started";
    server = new Server(2323);

    connect(server, &Server::applyData, this, slotApplyData);
}

void ServerInventory::slotApplyData(const QVector<int> &sentData)
{    
    qDebug() << sentData.size();
    int dropRow = sentData.at(0);
    int dropColumn = sentData.at(1);
    int dropValue = sentData.at(2);

    if (dropValue == 0)
    {
        qDebug() << dropRow << dropColumn;
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
    newItem->setBackground(QPixmap(":/images/red-apple.jpg").scaled(100, 100));
    if (sentData.size() == 5)
    {
        int dragRow = sentData.at(3);
        int dragColumn = sentData.at(4);
        this->setItem(dragRow, dragColumn, nullptr);
    }
    this->setItem(dropRow, dropColumn, newItem);

}
