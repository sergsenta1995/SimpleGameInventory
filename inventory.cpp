#include "inventory.hpp"
#include <QHeaderView>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QtWidgets>
#include <QDebug>

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
    setAcceptDrops(true);
    setDragDropOverwriteMode(false);
    setDragDropMode(QAbstractItemView::DragDrop);
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << event->mimeData()->text();

    foreach (QString str, event->mimeData()->formats()) {
        qDebug() << str << "\n";
    }
    if (event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
    else
        event->accept();
}

void Inventory::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug() << "dragMoveEvent";
    event->accept();
}

bool Inventory::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    QTableWidget::dropMimeData(row, column, data, action);
    qDebug() << "dropMimeData";
}

QStringList Inventory::mimeTypes() const
{
    qDebug() << "mimeTypes";

    return QTableWidget::mimeTypes() << QStringLiteral("text/plain") << QStringLiteral("application/x-qabstractitemmodeldatalist");
}

QMimeData* Inventory::mimeData(const QList<QTableWidgetItem *> items) const
{
    QString testValue = "123";
    QMimeData *data = QTableWidget::mimeData(items);
    data->setText(testValue);

    return data;
}
