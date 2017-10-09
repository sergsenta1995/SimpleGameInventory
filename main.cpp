#include "main-window.hpp"
#include <QApplication>
#include <QSqlQuery>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString db_type = "QSQLITE";
    if (!QSqlDatabase::drivers().contains(db_type))
    {
        qDebug() << "No QSQLITE driver found";
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(db_type);

    QDir workingDirectory("../");
    db.setDatabaseName(workingDirectory.absolutePath() + "/SimpleGameInventory/simple-inventory-db/simple_inventory_db.sqlite");

    if (!db.open())
    {
        qDebug() << "DB is not open";
        return a.exec();
    }
    else
        qDebug() << "Ok";

    MainWindow w;
    w.show();

    return a.exec();
}
