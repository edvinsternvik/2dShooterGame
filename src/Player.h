#pragma once
#include "Entity.h"
#include "BoxCollider.h"
#include <memory>

class Player : public Entity {
public:
    Player();
    virtual void update(float deltaTime) override;

public:
    float dir;
    std::shared_ptr<BoxCollider> boxCollider;

private:
    std::shared_ptr<Sprite> m_bulletSprite;
    float m_bulletCooldown;
};
