#include "client-game-object.hpp"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>
#include <QDebug>

ClientGameObject::ClientGameObject(QWidget *parent):
    GameObject(parent)
{
}

void ClientGameObject::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";

    QPixmap pixmap = *this->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    this->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
    {
        this->close();
    } else
    {
        this->show();
        this->setPixmap(pixmap);
    }
}

void ClientGameObject::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "move";
}
