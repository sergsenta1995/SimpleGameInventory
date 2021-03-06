#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QTableWidget>
#include "inventory-facade.hpp"

class InventoryFacade;

typedef QVector<QVector<QPair<int, QString>>> Content;
typedef QVector<QPair<int, QString>> CellContent;

/*!
 * \brief Базовый класс модели инвентаря.
 */
class Inventory : QObject{
    Q_OBJECT

public:
    explicit Inventory();
    //! Обновляет ячейку инвентаря с отправкой данных в базу.
    void update(int row, int column, int value, const QString &picture);
    //! Устанавливает данные в ячейку.
    void setupData(int row, int column, int value, const QString &picture);
    void setupSize(int dimension);    
    Content getContent();    

protected:
    InventoryFacade *facade;
    Content          content;
};

#endif // INVENTORY_HPP
