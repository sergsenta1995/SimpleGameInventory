#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QTableWidget>

class Inventory : public QTableWidget {
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);

private:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    bool dropMimeData(int row, int column,
                      const QMimeData *data,
                      Qt::DropAction action) override;
    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QList<QTableWidgetItem *> items) const override;
    void rewriteItem(int row, int column, int newValue);

    QTableWidgetItem *dragItem;
};

#endif // INVENTORY_HPP
