#ifndef INVENTORYFACADE_HPP
#define INVENTORYFACADE_HPP

#include "inventory.hpp"

class Inventory;

/*!
 * \brief Класс для работы с данными инвентаря.
 */
class InventoryFacade {
public:
    explicit InventoryFacade();
    //! Инициализирует ячейки инвентаря.
    void init(Inventory &inventory);
    //! Обновляет БД с содержимым инвентаря.
    void update(const QVector<int> &fieldsValue);
};

#endif // INVENTORYFACADE_HPP
