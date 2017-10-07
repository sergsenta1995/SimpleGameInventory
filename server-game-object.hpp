#ifndef SERVERGAMEOBJECT_HPP
#define SERVERGAMEOBJECT_HPP

#include "game-object.hpp"

class ServerGameObject : public GameObject {
public:
    explicit ServerGameObject(QWidget *parent = nullptr);
};

#endif // SERVERGAMEOBJECT_HPP
