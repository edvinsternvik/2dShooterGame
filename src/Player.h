#pragma once
#include "Entity.h"
#include "BoxCollider.h"
#include <memory>

class Player : public Entity {
public:
    Player();
    virtual void update(float deltaTime) override;

public:
    std::shared_ptr<BoxCollider> boxCollider;
};