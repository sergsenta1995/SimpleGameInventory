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

void InventoryWidget::init(const QVector<QVector<int> > &content)
{
    for(int i = 0; i < content.size(); ++i)
    {
        for (int j = 0; j < content[i].size(); ++j)
        {
            if (content[i][j] == 0)
                continue;

            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setText(QString::number(content[i][j]));
            newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
            QString picture = ":/images/red-apple.jpg";
            newItem->setBackground(QPixmap(picture).scaled(100, 100));
            this->setItem(i, j, newItem);
        }
    }
}
