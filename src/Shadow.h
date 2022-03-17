#pragma once
#include "Entity.h"
#include <memory>

class Shadow : public Entity {
public:
    Shadow(entityID target);
    virtual void update(float deltaTime) override;

private:
    const entityID m_target;
    static std::shared_ptr<Sprite> shadowSprite;
};
