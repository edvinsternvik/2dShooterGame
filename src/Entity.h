#pragma once
#include "Rendering/Sprite.h"
#include <memory>

class Shader;

class Entity {
public:
    Entity();
    virtual void update(float deltaTime) = 0;
    void render(Shader* shader);

    void setSprite(std::shared_ptr<Sprite> sprite);
    const Sprite* getSprite() const;

public:
    glm::vec2 pos;

private:
    std::shared_ptr<Sprite> m_entitySprite;
    bool m_destroyed;

    friend class EntityManager;
};

