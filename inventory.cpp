#include "inventory.hpp"

#include <QDebug>

Inventory::Inventory()
{
    facade->init(*this);
}

void Inventory::update(int row, int column, int value)
{
    if (value == 0)
        content[row][column].first = 0;
    else
        content[row][column].first += value;

    facade->update(row, column, content[row][column].first);
}

void Inventory::setValue(int row, int column, int value, const QString &picture)
{
    content[row][column].first = value;
    content[row][column].second = picture;
}

void Inventory::setupSize(int dimension)
{
    content = Content(dimension);

    for(int i = 0; i < dimension; i++)
        content[i] = CellContent(dimension);
}

Content Inventory::getContent()
{
    return content;
}
