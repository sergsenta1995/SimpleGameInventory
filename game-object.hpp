#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <QLabel>

class GameObject : public QLabel {
    Q_OBJECT

public:
    explicit GameObject(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void startDrag();
};

#endif // GAME_OBJECT_HPP
