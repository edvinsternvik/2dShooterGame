#include "Entity.h"

Entity::Entity()
    : pos(0), m_destroyed(false) {

}

void Entity::update(float deltaTime) {
}

void Entity::render(Shader* shader) {
    if(getSprite() != nullptr) {
        getSprite()->render(pos, 1.0, shader);
    }
}

void Entity::setSprite(std::shared_ptr<Sprite> sprite) {
    m_entitySprite = sprite;
}

const Sprite* Entity::getSprite() const {
    return m_entitySprite.get();
}

void Entity::markDestroyed() {
    m_destroyed = true;
}
