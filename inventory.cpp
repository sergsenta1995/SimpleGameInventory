#include "inventory.hpp"

Inventory::Inventory()
{

    facade->init(*this);
}

void Inventory::update(int row, int column, int value, const QString &picture)
{
    if (value == 0)
    {
        content[row][column].first = 0;
        content[row][column].second = "";
    }
    else
    {
        content[row][column].first += value;
        content[row][column].second = picture;
    }

    facade->update(row, column, content[row][column].first);
}


void Inventory::setupData(int row, int column, int value, const QString &picture)
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
