#pragma once
#include "Entity.h"
#include "BoxCollider.h"
#include <memory>

class Player : public Entity {
public:
    Player();
    virtual void update(float deltaTime) override;
    virtual void setPos(glm::vec2 newPos) override;

private:
    void collisionCallback(BoxCollider* other);

public:
    float dir;
    std::shared_ptr<BoxCollider> boxCollider;

private:
    std::shared_ptr<Sprite> m_bulletSprite;
    float m_bulletCooldown;
    float m_cameraShakeIntensity;
    float m_timer;
};
