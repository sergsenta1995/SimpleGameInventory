#ifndef CLIENT_GAMEOBJECT_HPP
#define CLIENT_GAMEOBJECT_HPP

#include "game-object.hpp"

/*!
 * \brief Класс предмета на стороне клиента.
 * \details Является источником drag 'n' drop.
 *          Инициализируется в базовом классе.
 */
class ClientGameObject : public GameObject {
public:
    explicit ClientGameObject(QWidget *parent = nullptr);
private:
    //! Событие, обрабатывающее нажатие клавиши на предмете.
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CLIENT_GAMEOBJECT_HPP
