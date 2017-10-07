#ifndef CLIENTGAMEOBJECT_HPP
#define CLIENTGAMEOBJECT_HPP

#include "game-object.hpp"

class ClientGameObject : public GameObject {
public:
    explicit ClientGameObject(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // CLIENTGAMEOBJECT_HPP
