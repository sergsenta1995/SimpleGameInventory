#include "client-inventory.hpp"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QItemSelectionModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QMimeData>
#include <QApplication>

/*!
 * \brief Класс-делегат, который настраивает прозрачность ячейки при перетаскивании.
 */
class TransparentSelectionItemStyle : public QStyledItemDelegate
{
public:
    explicit TransparentSelectionItemStyle(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const
    {
        QVariant background = index.data(Qt::BackgroundRole);
        if (background.canConvert<QBrush>())
            painter->fillRect(option.rect, background.value<QBrush>());

        painter->drawText(option.rect, index.data(Qt::DisplayRole).toString(), QTextOption(Qt::AlignRight | Qt::AlignBottom));
        QStyledItemDelegate::paint(painter, option, index);
    }
};

ClientInventory::ClientInventory(QWidget *parent):
    Inventory(parent),
    dragItem(nullptr),
    player(new QMediaPlayer)
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    setDragDropOverwriteMode(false);
    setDragDropMode(QAbstractItemView::DragDrop);

    player->setMedia(QUrl("qrc:/sounds/bite-apple.mp3"));
    player->setVolume(50);   

    setItemDelegate(new TransparentSelectionItemStyle(this));
    setStyleSheet("selection-background-color: rgba(128, 128, 128, 0);");
}

void ClientInventory::startClient()
{
    client = new Client("localhost", 2323);
}

void ClientInventory::dragEnterEvent(QDragEnterEvent *event)
{        
    event->accept();    
    dragItem = itemAt(event->pos());    
}

void ClientInventory::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

bool ClientInventory::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{    
    int dragValue = data->text().toInt();
    QString type = data->property("type").toString();
    QString picture = data->property("picture").toString();
    qDebug() << "type " << type << "; value " << dragValue << "; picture " << picture;

    // Подняли ячейку и отпустили туда же или
    if ((dragItem != nullptr && dragItem->row() == row && dragItem->column() == column) ||
    // или перетаскиваемый предмет из ячейки пуст.
        (dragItem == nullptr && dragValue == 0 && data->formats().at(0) == "application/x-qabstractitemmodeldatalist"))
    {
        return true;
    }

    // Перетаскиваем предмет в инвентарь.
    if (dragValue == 0 && dragItem == nullptr)
    {
        client->sendToServer(QVector<int>{row, column, 1});

        rewriteItem(row, column, 1, QStringList{type, picture});
        dragItem = nullptr;
        return true;
    }

    // Перетаскиваем между ячейками (перетаскиваемая не пуста).    
    rewriteItem(row, column, dragValue, QStringList{type, picture});
    client->sendToServer(QVector<int>{row, column, dragValue, dragItem->row(), dragItem->column()});
    facade->update({1, dragItem->row(), dragItem->column(), 0});
    setItem(dragItem->row(), dragItem->column(), nullptr);

    // Затираем перетаскиваемое.
    dragItem = nullptr;

    return true;
}

QStringList ClientInventory::mimeTypes() const
{
    return QTableWidget::mimeTypes() << QStringLiteral("text/plain")
                                     << QStringLiteral("application/x-qabstractitemmodeldatalist")
                                     << QStringLiteral("application/x-dnditemdata");
}


QMimeData* ClientInventory::mimeData(const QList<QTableWidgetItem *> items) const
{
    QMimeData *data = QTableWidget::mimeData(items);
    if (items.at(0) == nullptr)
    {        
        data->setText("0");        
        return data;
    }

    const int TYPE    = 0;
    const int PICTURE = 1;

    // Дополнительные сведения о предмете будем хранить в пользовательской роли.
    data->setProperty("type", items.at(0)->data(Qt::UserRole).toStringList().at(TYPE));
    data->setProperty("picture", items.at(0)->data(Qt::UserRole).toStringList().at(PICTURE));
    data->setText(items.at(0)->text());      

    return data;
}

void ClientInventory::rewriteItem(int row, int column, int newValue, const QVariant &userData)
{    
    const int TYPE    = 0;
    const int PICTURE = 1;

    QTableWidgetItem *newItem = item(row, column);
    if (newItem == nullptr)
    {
        newItem = new QTableWidgetItem;
        newItem->setText(QString::number(newValue));
        newItem->setData(Qt::UserRole, userData);
        facade->update({1, row, column, newValue});
    }
    else
    {
        int oldValue = newItem->data(Qt::DisplayRole).toInt();
        newItem->setText(QString::number(oldValue + newValue));        
        facade->update({1, row, column, oldValue + newValue});
    }
    newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
    newItem->setBackground(QPixmap(userData.toStringList().at(PICTURE)).scaled(100, 100));

    this->setItem(row, column, newItem);
}

void ClientInventory::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        QTableWidgetItem *tempItem = itemAt(event->pos());

        if (tempItem == nullptr)
            return;

        int value = tempItem->data(Qt::DisplayRole).toInt();
        --value;

        player->stop();
        player->play();

        if (value == 0)
        {
            client->sendToServer(QVector<int>{tempItem->row(), tempItem->column(), 0});
            setItem(tempItem->row(), tempItem->column(), nullptr);
            return;
        }

        client->sendToServer(QVector<int>{tempItem->row(), tempItem->column(), -1});

        tempItem->setData(Qt::DisplayRole, value);
    }

    QTableWidget::mousePressEvent(event);
}
