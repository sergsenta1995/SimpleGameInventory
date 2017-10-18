#ifndef INVENTORYFACADE_HPP
#define INVENTORYFACADE_HPP

#include "inventory.hpp"

class Inventory;

/*!
 * \brief Класс для работы с данными инвентаря.
 */
class InventoryFacade : QObject{
    Q_OBJECT
public:
    explicit InventoryFacade();
    //! Инициализирует ячейки инвентаря.
    void init(Inventory &inventory);
    //! Обновляет БД с содержимым инвентаря.
    void update(int row, int column, int value);
};

#endif // INVENTORYFACADE_HPP
