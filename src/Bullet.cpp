#include "Bullet.h"
#include <iostream>

Bullet::Bullet() 
    : boxCollider(std::make_shared<BoxCollider>(false)) {


    std::function<void(BoxCollider*)> callbackFn = [&](BoxCollider* boxCollider) {
        collisionCallback(boxCollider);
    };

    boxCollider->setCollisionCallback(callbackFn);
}

void Bullet::update(float deltaTime) {
    pos.x += deltaTime * 10.0;
    boxCollider->updatePos(pos, glm::vec2(0.25, 0.25));
}

void Bullet::collisionCallback(BoxCollider* other) {
    markDestroyed();
}
