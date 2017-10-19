#ifndef SERVER_INVENTORY_HPP
#define SERVER_INVENTORY_HPP

#include "inventory-widget.hpp"
#include "server.hpp"
#include "inventory-facade.hpp"

/*!
 * \brief Класс инвентаря на стороне сервера.
 * \details Не поддерживает drag 'n' drop, принимает изменения от виджета на стороне клиента.
 *          Визуальная составляющая инициализируется в базовом классе.
 */
// FIX: Пустой класс. Можно удалять и использовать базовый?
class ServerInventory : public InventoryWidget {
    Q_OBJECT

public:
    explicit ServerInventory(QWidget *parent = nullptr);
};

#endif // SERVER_INVENTORY_HPP
