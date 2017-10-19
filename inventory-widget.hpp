#ifndef INVENTORYWIDGET_HPP
#define INVENTORYWIDGET_HPP

#include <QTableWidget>

typedef QVector<QVector<QPair<int, QString>>> Content;

class InventoryWidget : public QTableWidget {
    Q_OBJECT
public:
    explicit InventoryWidget(QWidget *parent = nullptr);
    void init(const Content &content);
    virtual void rewriteItem(int row, int column, int newValue, const QString &picture) = 0;

signals:
    void changeCellData(int row, int column, int value, const QString &picture);
};

#endif // INVENTORYWIDGET_HPP
