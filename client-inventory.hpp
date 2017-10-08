#ifndef CLIENTINVENTORY_HPP
#define CLIENTINVENTORY_HPP

#include <QMediaPlayer>
#include "inventory.hpp"
#include "client.hpp"
#include "database-facade.hpp"

class DatabaseFacade;

class ClientInventory : public Inventory {
public:
    explicit ClientInventory(QWidget *parent = nullptr);
    void startClient();

private:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    bool dropMimeData(int row,
                      int column,
                      const QMimeData *data,
                      Qt::DropAction action) override;
    QStringList mimeTypes() const override;
    QMimeData* mimeData(const QList<QTableWidgetItem *> items) const override;
    void rewriteItem(int row, int column, int newValue);
    void mousePressEvent(QMouseEvent *event) override;    

    QTableWidgetItem *dragItem;
    QMediaPlayer     *player;
    Client           *client;    
    DatabaseFacade   *facade;
};

#endif // CLIENTINVENTORY_HPP
