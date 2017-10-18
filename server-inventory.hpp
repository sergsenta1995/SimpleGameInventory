#ifndef SERVERINVENTORY_HPP
#define SERVERINVENTORY_HPP

#include "inventory-widget.hpp"
#include "server.hpp"
#include "inventory-facade.hpp"

/*!
 * \brief Класс инвентаря на стороне сервера.
 * \details Не поддерживает drag 'n' drop, принимает изменения от виджета на стороне клиента.
 *          Визуальная составляющая инициализируется в базовом классе.
 */
class ServerInventory : public InventoryWidget {
    Q_OBJECT

public:
    explicit ServerInventory(QWidget *parent = nullptr);
    //! Инициализирует объект ервера, который отвечает за приём данных.
    void startServer();

public slots:
    //! Применяет изменения виджета отосланные от клиента.
    //void slotApplyData(const QVector<int> &sentData);
    void slotApplyData(int dropRow, int dropColumn, int dropValue);

private:
    Server *server; ///< объект для приёма данных от клиента
};

#endif // SERVERINVENTORY_HPP
