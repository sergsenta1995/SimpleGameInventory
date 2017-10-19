#ifndef GAME_OBJECT_FACADE_HPP
#define GAME_OBJECT_FACADE_HPP

#include "game-object.hpp"

class GameObject;

/*!
 * \brief Класс для работы с данными предмета.
 */
class GameObjectFacade {
public:
    explicit GameObjectFacade();
    //! Инициализирует виджет данными из БД.
    void init(GameObject &gameObject);
};

#endif // GAME_OBJECT_FACADE_HPP
