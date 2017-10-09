#ifndef GAMEOBJECTFACADE_HPP
#define GAMEOBJECTFACADE_HPP

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

#endif // GAMEOBJECTFACADE_HPP
