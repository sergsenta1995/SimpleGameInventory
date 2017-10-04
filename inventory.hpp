#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QTableWidget>

class Inventory : public QTableWidget {
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    bool dropMimeData(int row, int column,
                      const QMimeData *data,
                      Qt::DropAction action) override;
    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QList<QTableWidgetItem *> items) const override;
};

#endif // INVENTORY_HPP
