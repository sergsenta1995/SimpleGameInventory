#include "client-inventory.hpp"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QItemSelectionModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QMimeData>
#include <QApplication>

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
    Inventory(parent)
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    setDragDropOverwriteMode(false);
    setDragDropMode(QAbstractItemView::DragDrop);

    dragItem = nullptr;

    player = new QMediaPlayer;
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
    qDebug() << "drag enter";
    if (dragItem == nullptr)
        qDebug() << "dragItem == nullptr";
    else
        qDebug() << "else " << dragItem->row() << dragItem->column();
    event->accept();

    qDebug() << "POOOS!" << event->pos();

    dragItem = itemAt(event->pos());

    if (dragItem == nullptr)
        qDebug() << "2 dragItem == nullptr";
    else
        qDebug() << "2 else " << dragItem->row() << dragItem->column();
}

void ClientInventory::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

bool ClientInventory::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{    
    bool f1 = item(0,0) == nullptr;
    bool f2 = item(1,2) == nullptr;
    qDebug() << "NULLPTR is ============" << f1 << f2;

    int dragValue = data->text().toInt();


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
        qDebug() << "cell<->QLabel";
        client->slotSendToServer(row, column, 1);
        rewriteItem(row, column, 1);
        dragItem = nullptr;
        return true;
    }

    // Перетаскиваем между ячейками (перетаскиваемая не пуста).
    rewriteItem(row, column, dragValue);
    qDebug() << dragItem->row() << dragItem->column();
    client->slotSendToServer(row, column, dragValue, dragItem->row(), dragItem->column());
    setItem(dragItem->row(), dragItem->column(), nullptr);

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

    data->setText(items.at(0)->text());

    return data;
}

void ClientInventory::rewriteItem(int row, int column, int newValue)
{    
    QTableWidgetItem *newItem = item(row, column);
    if (newItem == nullptr)
    {
        newItem = new QTableWidgetItem;
        newItem->setText(QString::number(newValue));
    }
    else
    {
        int oldValue = newItem->data(Qt::DisplayRole).toInt();
        newItem->setText(QString::number(oldValue + newValue));
    }
    newItem->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
    newItem->setBackground(QPixmap(":/images/red-apple.jpg").scaled(100, 100));
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
            client->slotSendToServer(tempItem->row(), tempItem->column(), 0);
            setItem(tempItem->row(), tempItem->column(), nullptr);
            return;
        }

        client->slotSendToServer(tempItem->row(), tempItem->column(), -1);

        tempItem->setData(Qt::DisplayRole, value);
    }

    QTableWidget::mousePressEvent(event);
}
