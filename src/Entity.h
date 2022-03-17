#pragma once
#include "Rendering/Sprite.h"
#include <memory>

class Shader;

using entityID = uint32_t;

class Entity {
public:
    Entity();
    virtual ~Entity();
    virtual void update(float deltaTime);
    void render(Shader* shader);

    void setSprite(std::shared_ptr<Sprite> sprite);
    Sprite* getSprite() const;
    glm::vec2 getPos() const;
    virtual void setPos(glm::vec2 newPos);
    void markDestroyed();

private:
    glm::vec2 m_pos;
    std::shared_ptr<Sprite> m_entitySprite;
    bool m_destroyed;

    friend class EntityManager;
};

