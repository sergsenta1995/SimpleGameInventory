#include "game-object.hpp"

GameObject::GameObject(QWidget *parent) :
    QLabel(parent)
{
    setFixedSize(100,100);
    setPixmap(QPixmap(":/images/red-apple.jpg").scaled(100, 100));
}
