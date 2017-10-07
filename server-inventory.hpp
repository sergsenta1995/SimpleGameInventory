#ifndef SERVERINVENTORY_HPP
#define SERVERINVENTORY_HPP

#include "inventory.hpp"
#include "server.hpp"

class ServerInventory : public Inventory {
    Q_OBJECT

public:
    explicit ServerInventory(QWidget *parent = nullptr);
    void startServer();

public slots:
    void applyInventoryToInventoryChange(int dropRow, int dropColumn, int dropValue, int dragRow, int dragColumn);
    void applyObjectToInventoryChange(int dropRow, int dropColumn, int dropValue);

private:
    Server *server;
};

#endif // SERVERINVENTORY_HPP
