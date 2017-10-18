#include "inventory.hpp"

#include <QDebug>

Inventory::Inventory()
{
    facade->init(*this);
}

void Inventory::update(int row, int column, int value)
{
    if (value == 0)
        content[row][column] = 0;
    else
        content[row][column] += value;

    facade->update(row, column, content[row][column]);
}

void Inventory::setValue(int row, int column, int value)
{
    content[row][column] = value;
}

void Inventory::setupSize(int dimension)
{
    content = QVector<QVector<int>>(dimension);

    for(int i = 0; i < dimension; i++)
        content[i] = QVector<int>(dimension);
}

QVector<QVector<int> > Inventory::getContent()
{
    return content;
}
