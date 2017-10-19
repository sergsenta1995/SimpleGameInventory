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
    InventoryWidget(parent),
    dragItem(nullptr),
    player(new QMediaPlayer)
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    setDragDropOverwriteMode(true);
    setDragDropMode(QAbstractItemView::DragDrop);

    player->setMedia(QUrl("qrc:/sounds/bite-apple.mp3"));
    player->setVolume(50);

    setItemDelegate(new TransparentSelectionItemStyle(this));
    setStyleSheet("selection-background-color: rgba(128, 128, 128, 0);");
}

void ClientInventory::dragEnterEvent(QDragEnterEvent *event)
{
    // Если предмет захвачен, продолжать его держать.
    if (dragItem != nullptr)
    {
        event->accept();
        return;
    }

    event->accept();    

    // Захватываем ячейку.
    if (itemAt(event->pos()) == nullptr)
        return;
    else            
        dragItem = itemAt(event->pos());    
}

void ClientInventory::dragMoveEvent(QDragMoveEvent *event)
{
}

bool ClientInventory::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    int dragValue = data->text().toInt();
    QString picture  = data->property("picture").toString();

    // Перетаскивание предмета в инвентарь.
    if (data->formats().at(0) == "application/x-dnditemdata")
    {        
        emit changeCellData(row, column, 1, picture);
        rewriteItem(row, column, 1, picture);
        dragItem = nullptr;
        return true;
    }

    // Перетаскивание ячейки инветраря.

    // Перетаскиваемая ячейка пуста.
    if (dragItem == nullptr)
        return true;

    // Подняли ячейку и отпустили туда же или
    if (dragItem != nullptr && dragItem->row() == row && dragItem->column() == column)
    {
        dragItem = nullptr;
        return true;
    }

    // Перетаскиваем между ячейками (перетаскиваемая не пуста).

    emit changeCellData(row, column, dragValue, picture);
    rewriteItem(row, column, dragValue, picture);

    emit changeCellData(dragItem->row(), dragItem->column(), 0, "");
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
    data->setProperty("picture", items.at(0)->data(Qt::UserRole));

    return data;    
}

void ClientInventory::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        QTableWidgetItem *tempItem = itemAt(event->pos());

        if (tempItem == nullptr)
            return;

        int value = tempItem->data(Qt::DisplayRole).toInt();
        QString picture = tempItem->data(Qt::UserRole).toString();
        --value;

        player->stop();
        player->play();

        if (value == 0)
        {            
            emit changeCellData(tempItem->row(), tempItem->column(), 0, picture);
            setItem(tempItem->row(), tempItem->column(), nullptr);
            return;
        }

        emit changeCellData(tempItem->row(), tempItem->column(), -1, picture);

        tempItem->setData(Qt::DisplayRole, value);
    }

    QTableWidget::mousePressEvent(event);
}
