#ifndef INVENTORYWIDGET_HPP
#define INVENTORYWIDGET_HPP

#include <QTableWidget>

class InventoryWidget : public QTableWidget {
    Q_OBJECT
public:
    explicit InventoryWidget(QWidget *parent = nullptr);
    void init(const QVector<QVector<int>> &content);

signals:
    void changeCellData(int row, int column, int value);
};

#endif // INVENTORYWIDGET_HPP
