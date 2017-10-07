#include "server.hpp"

Server::Server(int port):
    nextBlockSize(0)
{        
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Ошибка. Сервер не стартовал:"
                 << errorString();
        close();    // ???
        return;
    }
    connect(this, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));    
}

void Server::slotNewConnection()
{
    qDebug() << "new connection";
    QTcpSocket* clientSocket = nextPendingConnection();
    connect(clientSocket, SIGNAL(disconnected()),  clientSocket, SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(readyRead()),     this,         SLOT(slotReadClient()));
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_9);
    for (;;) {
        if (!nextBlockSize) {
            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < nextBlockSize) {
            break;
        }

        int numArguments, dropRow, dropColumn, dropValue, dragRow, dragColumn;
        in >> numArguments;

        if (numArguments == 3)
        {
            in >> dropRow >> dropColumn >> dropValue;
            emit acceptedObjectToInventoryData(dropRow, dropColumn, dropValue);
        }
        else
        {
            in >> dropRow >> dropColumn >> dropValue >> dragRow >> dragColumn;
            emit acceptedInventoryToInventoryData(dropRow, dropColumn, dropValue, dragRow, dragColumn);
        }

        nextBlockSize = 0;
    }
}
