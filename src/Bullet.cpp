#include "Bullet.h"
#include "Game.h"

Bullet::Bullet() 
    : dir(0), boxCollider(std::make_shared<BoxCollider>(false)) {

    std::function<void(BoxCollider*)> callbackFn = [&](BoxCollider* boxCollider) {
        collisionCallback(boxCollider);
    };

    boxCollider->setCollisionCallback(callbackFn);
    boxCollider->collisionLayer = 3;
    Game::collisionManager.registerCollider(boxCollider);
}

void Bullet::update(float deltaTime) {
    float bulletSpeed = 16.0;
    pos.x += deltaTime * bulletSpeed * std::cos(dir);
    pos.y += deltaTime * bulletSpeed * std::sin(dir);

    boxCollider->updatePos(pos, glm::vec2(0.25, 0.25));
}

void Bullet::collisionCallback(BoxCollider* other) {
    markDestroyed();
}
