#include "server.hpp"

Server::Server(int port):
    nextBlockSize(0)
{        
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Ошибка. Сервер не стартовал:"
                 << errorString();
        close();
        return;
    }
    connect(this, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));    
}

void Server::slotNewConnection()
{   
    QTcpSocket* clientSocket = nextPendingConnection();
    connect(clientSocket, SIGNAL(disconnected()),  clientSocket, SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(readyRead()),     this,         SLOT(slotReadClient()));
}

void Server::slotReadClient()
{    
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_9);
    for (;;)
    {
        if (!nextBlockSize)
        {
            if (clientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }

        if (clientSocket->bytesAvailable() < nextBlockSize) {
            break;
        }

        int row = 0;
        in >> row;

        int column = 0;
        in >> column;

        int value = 0;
        in >> value;

        QByteArray picture;
        in >> picture;
        QString pic = picture;

        emit applyData(row, column, value, pic);

        nextBlockSize = 0;
    }
}
