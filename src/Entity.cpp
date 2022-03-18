#include "Entity.h"

Entity::Entity()
    : depthOffset(0.0), m_pos(0), m_destroyed(false) {

}

Entity::~Entity() {
}

void Entity::update(float deltaTime) {
}

void Entity::render(Shader* shader) {
    if(getSprite() != nullptr) {
        getSprite()->render(getPos(), 1.0, 0.0, depthOffset, shader);
    }
}

void Entity::setSprite(std::shared_ptr<Sprite> sprite) {
    m_entitySprite = sprite;
}

Sprite* Entity::getSprite() const {
    return m_entitySprite.get();
}

glm::vec2 Entity::getPos() const {
    return m_pos;
}

void Entity::setPos(glm::vec2 newPos) {
    m_pos = newPos;
}

void Entity::markDestroyed() {
    m_destroyed = true;
}
