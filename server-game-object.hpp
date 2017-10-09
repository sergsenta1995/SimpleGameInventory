#ifndef SERVERGAMEOBJECT_HPP
#define SERVERGAMEOBJECT_HPP

#include "game-object.hpp"

/*!
 * \brief Предмет на стороне сервера.
 * \details Не является источником drag 'n' drop.
 *          Инициализируется в базовом классе.
 */
// FIX: Пустой класс. Можно удалить и использовать базовый.
class ServerGameObject : public GameObject {
public:
    explicit ServerGameObject(QWidget *parent = nullptr);
};

#endif // SERVERGAMEOBJECT_HPP
