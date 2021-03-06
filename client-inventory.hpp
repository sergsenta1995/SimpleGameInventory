#ifndef CLIENT_INVENTORY_HPP
#define CLIENT_INVENTORY_HPP

#include <QMediaPlayer>
#include "inventory-widget.hpp"
#include "client.hpp"
#include "inventory-facade.hpp"

/*!
 * \brief Класс инвентаря на стороне клиента.
 * \details Поддерживает drag 'n' drop, отправляет изменения инвентаря в базу.
 *          Визуальная составляющая инициализируется в базовом классе.
 */
class ClientInventory : public InventoryWidget {
    Q_OBJECT
public:
    explicit ClientInventory(QWidget *parent = nullptr);    

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

    QTableWidgetItem *dragItem; ///< перетаскиваемый элемент ячейки
    QMediaPlayer     *player;   ///< объект для воспроизведения звука откумывания яблока    
};

#endif // CLIENT_INVENTORY_HPP
