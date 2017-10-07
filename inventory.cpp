#include "inventory.hpp"

#include <QHeaderView>


Inventory::Inventory(QWidget *parent) :
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

