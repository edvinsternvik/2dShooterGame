#pragma once
#include "BoxCollider.h"
#include "Entity.h"
#include <memory>

class Bullet : public Entity {
public:
    Bullet();
    virtual void update(float deltaTime) override;
    virtual void setPos(glm::vec2 newPos) override;

private:
    void collisionCallback(BoxCollider* other);

public:
    float speed;
    float dir;
    std::shared_ptr<BoxCollider> boxCollider;
};

