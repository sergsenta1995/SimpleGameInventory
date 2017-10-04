#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <QTableWidget>

class Inventory : public QTableWidget {
    Q_OBJECT

public:
    Inventory(QWidget *parent = nullptr);
};

#endif // INVENTORY_HPP
