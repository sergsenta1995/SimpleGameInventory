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

        QVector<int> sentData;

        int dataSize;
        in >> dataSize;
        for (int i = 0; i < dataSize; ++i)
        {
            int element;
            in >> element;
            sentData << element;
        }

        emit applyData(sentData);

        nextBlockSize = 0;
    }
}
