#pragma once
#include "BoxCollider.h"
#include "Entity.h"
#include "EntityManager.h"
#include <memory>

class Enemy : public Entity {
public:
    Enemy();

    virtual void update(float deltaTime) override;
    virtual void setPos(glm::vec2 newPos) override;

    void setTarget(entityID target);

private:
    void collisionCallback(BoxCollider* other);

private:
    int health;
    float m_bulletCooldown;
    entityID m_targetEntity;
    
    std::shared_ptr<BoxCollider> boxCollider;
    std::shared_ptr<Sprite> m_bulletSprite;
};
