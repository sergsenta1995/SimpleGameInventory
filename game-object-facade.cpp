#include "game-object-facade.hpp"
#include <QSqlQuery>
#include <QVariant>

GameObjectFacade::GameObjectFacade()
{
}


void GameObjectFacade::init(GameObject &gameObject)
{
    QSqlQuery query;
    query.prepare("SELECT * "
                  "FROM game_object "
                  "WHERE id = ? ");
    // NOTE: По умочлчанию первый предмет,
    //       т. к. возможноть выбора предмета не предусматривалась.
    query.addBindValue(1);
    query.exec();

    query.next();
    gameObject.setPixmap(QPixmap(query.value("picture").toString()).scaled(100, 100));
    gameObject.setType(query.value("type").toString());
    gameObject.setPicture(query.value("picture").toString());
}
