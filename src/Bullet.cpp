#include "Bullet.h"
#include "Game.h"

Bullet::Bullet() 
    : dir(0), speed(1.0), boxCollider(std::make_shared<BoxCollider>(false)) {

    std::function<void(BoxCollider*)> callbackFn = [&](BoxCollider* boxCollider) {
        collisionCallback(boxCollider);
    };

    boxCollider->setCollisionCallback(callbackFn);
    Game::collisionManager.registerCollider(boxCollider);
}

void Bullet::update(float deltaTime) {
    glm::vec2 newPos = getPos();
    newPos.x += deltaTime * speed * std::cos(dir);
    newPos.y += deltaTime * speed * std::sin(dir);
    setPos(newPos);
}

void Bullet::setPos(glm::vec2 newPos) {
    Entity::setPos(newPos);
    boxCollider->updatePos(getPos(), glm::vec2(0.25, 0.25));
}

void Bullet::collisionCallback(BoxCollider* other) {
    markDestroyed();
}
