#include "inventory.hpp"
#include <QHeaderView>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QtWidgets>
#include <QDebug>
#include <QItemSelectionModel>

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

Inventory::Inventory(QWidget *parent) :
    QTableWidget(parent)
{
    verticalHeader()->hide();
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    horizontalHeader()->hide();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setColumnCount(3);
    setRowCount(3);
    setFixedSize(300,300);

    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    setDragDropOverwriteMode(false);
    setDragDropMode(QAbstractItemView::DragDrop);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setItemDelegate(new TransparentSelectionItemStyle(this));
    setStyleSheet("selection-background-color: rgba(128, 128, 128, 0);");

    dragItem = new QTableWidgetItem;

    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/bite-apple.mp3"));
    player->setVolume(50);

    client = new Client("localhost", 2323);
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    dragItem = itemAt(event->pos());
    event->accept();
}

void Inventory::dragMoveEvent(QDragMoveEvent *event)
{        
    event->accept();
}

bool Inventory::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{        
    if (dragItem != nullptr && dragItem->row() == row && dragItem->column() == column)
        return true;

    if (data->formats().constFirst() == "application/x-dnditemdata")
    {
        QTableWidgetItem *tempItem = item(row, column);
        if (tempItem == nullptr)
        {
            rewriteItem(row, column, 1);
            client->slotSendToServer(row, column, 1);
            return true;
        }

        int value = item(row, column)->text().toInt();
        ++value;
        rewriteItem(row, column, value);
        client->slotSendToServer(row, column, value);
        return true;
    }

    if (data->formats().constFirst() == "application/x-qabstractitemmodeldatalist")
    {
        int value = data->text().toInt();

        if (value == 0)
            return true;

        if (item(row, column) == nullptr)
        {
            rewriteItem(row, column, value);
            setItem(dragItem->row(), dragItem->column(), new QTableWidgetItem);
        }
        else
        {
            value += item(row, column)->data(0).toInt();
            rewriteItem(row, column, value);
            setItem(dragItem->row(), dragItem->column(), new QTableWidgetItem);
        }

        client->slotSendToServer(row, column, value);
    }

    return true;
}

QStringList Inventory::mimeTypes() const
{
    return QTableWidget::mimeTypes() << QStringLiteral("text/plain")
                                     << QStringLiteral("application/x-qabstractitemmodeldatalist")
                                     << QStringLiteral("application/x-dnditemdata");
}


QMimeData* Inventory::mimeData(const QList<QTableWidgetItem *> items) const
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

void Inventory::rewriteItem(int row, int column, int newValue)
{
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setText(QString::number(newValue));
    item->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
    item->setBackground(QPixmap(":/images/red-apple.jpg").scaled(100, 100));
    this->setItem(row, column, item);
}

void Inventory::mousePressEvent(QMouseEvent *event)
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
            setItem(tempItem->row(), tempItem->column(), new QTableWidgetItem);
            return;
        }

        tempItem->setData(Qt::DisplayRole, value);
    }

    QTableWidget::mousePressEvent(event);
}
