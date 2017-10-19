#ifndef INVENTORY_WIDGET_HPP
#define INVENTORY_WIDGET_HPP

#include <QTableWidget>

typedef QVector<QVector<QPair<int, QString>>> Content;

/*!
 * \brief Базовый класс для отображения инвентаря.
 */
class InventoryWidget : public QTableWidget {
    Q_OBJECT

public:
    explicit InventoryWidget(QWidget *parent = nullptr);
    //! Заполнение данными из модели.
    void init(const Content &content);
    //! Перезаписывает содержимое ячейки.
    void rewriteItem(int row, int column, int newValue, const QString &picture);

signals:
    //! Сигнал изменения ячейки, на который откликается модель.
    void changeCellData(int row, int column, int value, const QString &picture);
};

#endif // INVENTORY_WIDGET_HPP
