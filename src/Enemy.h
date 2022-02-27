#pragma once
#include "BoxCollider.h"
#include "Entity.h"
#include <memory>

class Enemy : public Entity {
public:
    Enemy();
    virtual void setPos(glm::vec2 newPos) override;

private:
    void collisionCallback(BoxCollider* other);

private:
    int health;
    
    std::shared_ptr<BoxCollider> boxCollider;
};
