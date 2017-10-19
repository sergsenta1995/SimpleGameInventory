#include "inventory-widget.hpp"
#include <QHeaderView>
#include <QSqlResult>

InventoryWidget::InventoryWidget(QWidget *parent) :
    QTableWidget(parent)
{
    verticalHeader()->hide();
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setColumnCount(3);
    setRowCount(3);
    setFixedSize(300,300);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

void InventoryWidget::init(const Content &content)
{
    for(int i = 0; i < content.size(); ++i)
    {
        for (int j = 0; j < content[i].size(); ++j)
        {
            if (content[i][j].first == 0)
                continue;

            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setText(QString::number(content[i][j].first));

            QString picture = content[i][j].second;
            newItem->setData(Qt::UserRole, picture);

            newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);            
            newItem->setBackground(QPixmap(picture).scaled(100, 100));            
            this->setItem(i, j, newItem);
        }
    }
}

void InventoryWidget::rewriteItem(int row, int column, int newValue, const QString &picture)
{
    if (newValue == 0)
    {
        this->setItem(row, column, nullptr);
        return;
    }

    QTableWidgetItem *newItem = item(row, column);
    if (newItem == nullptr)
    {
        newItem = new QTableWidgetItem;
        newItem->setText(QString::number(newValue));
    }
    else
    {
        int oldValue = newItem->data(Qt::DisplayRole).toInt();
        newItem->setText(QString::number(oldValue + newValue));
    }
    newItem->setData(Qt::UserRole,picture);

    newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
    newItem->setBackground(QPixmap(picture).scaled(100, 100));
    this->setItem(row, column, newItem);
}
