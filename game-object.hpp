#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <QLabel>
#include "game-object-facade.hpp"

class GameObjectFacade;

/*!
 * \brief Класс предмета.
 * \details Базовый класс для клиентского и серверного виджета.
 *          Инициализируется данными из БД.
 */
class GameObject : public QLabel {
    Q_OBJECT

public:
    explicit GameObject(QWidget *parent = nullptr);
    void setType(const QString type_);
    void setPicture(const QString picture_);
protected:
    QString           type;     ///< тип предмета
    QString           picture;  ///< путь к картинке предмета
    GameObjectFacade *facade;   ///< объект для работы с данными предмета из БД
};

#endif // GAME_OBJECT_HPP
