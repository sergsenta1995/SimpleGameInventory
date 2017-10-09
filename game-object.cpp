#include "game-object.hpp"

GameObject::GameObject(QWidget *parent) :
    QLabel(parent)
{
    setFixedSize(100,100);

    facade->init(*this);
}

void GameObject::setType(const QString type_)
{
    type = type_;
}

void GameObject::setPicture(const QString picture_)
{
    picture = picture_;
}
