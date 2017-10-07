#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QTableWidget>

class Inventory : public QTableWidget {
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);
};

#endif // INVENTORY_HPP
