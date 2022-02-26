#pragma once
#include "BoxCollider.h"
#include "Entity.h"
#include <memory>

class Bullet : public Entity {
public:
    Bullet();
    virtual void update(float deltaTime) override;

private:
    void collisionCallback(BoxCollider* other);

public:
    std::shared_ptr<BoxCollider> boxCollider;
};

