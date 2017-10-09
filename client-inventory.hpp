#ifndef CLIENT_INVENTORY_HPP
#define CLIENT_INVENTORY_HPP

#include <QMediaPlayer>
#include "inventory.hpp"
#include "client.hpp"
#include "inventory-facade.hpp"

/*!
 * \brief Класс инвентаря на стороне клиента.
 * \details Поддерживает drag 'n' drop, отправляет изменения инвентаря в базу.
 *          Визуальная составляющая инициализируется в базовом классе.
 */
class ClientInventory : public Inventory {
public:
    explicit ClientInventory(QWidget *parent = nullptr);
    //! Инициализирует объект клиента, который отвечает за отправку данных на сервер.
    void startClient();    

private:
    //! Событие, обрабатывающее пересечение границ виджета перетаскиваемым объектом.
    void dragEnterEvent(QDragEnterEvent *event) override;
    //! Событие, обрабатывающее движение перетаскиваемого объекта в области виджета.
    void dragMoveEvent(QDragMoveEvent *event) override;
    //! Управляет отпущенными в ячейку данными.
    bool dropMimeData(int row,
                      int column,
                      const QMimeData *data,
                      Qt::DropAction action) override;
    QStringList mimeTypes() const override;
    //! Возвращает список типов, которые могут использоваться для описания перетаскиваемого объекта.
    QMimeData* mimeData(const QList<QTableWidgetItem *> items) const override;
    //! Событие, обрабатывающее нажатие клавиши мыши на виджете.
    void mousePressEvent(QMouseEvent *event) override;
    //! Перезаписывает ячейку после перетаскивания.
    void rewriteItem(int row, int column, int newValue, const QVariant &userData = QStringList());

    QTableWidgetItem *dragItem; ///< перетаскиваемый элемент ячейки
    QMediaPlayer     *player;   ///< объект для воспроизведения звука откумывания яблока
    Client           *client;   ///< объект для отправки данных на сервер
};

#endif // CLIENT_INVENTORY_HPP
