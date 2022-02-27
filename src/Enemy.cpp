#include "Enemy.h"
#include "Game.h"

Enemy::Enemy()
    : boxCollider(std::make_shared<BoxCollider>(false)) {
    
    boxCollider->collisionLayer = 2;
    boxCollider->setCollisionCallback(std::bind(&Enemy::collisionCallback, this, std::placeholders::_1));
    Game::collisionManager.registerCollider(boxCollider);
    health = 20;
}

void Enemy::setPos(glm::vec2 newPos) {
    Entity::setPos(newPos);
    boxCollider->updatePos(newPos, glm::vec2(1.0, 1.0));
}

void Enemy::collisionCallback(BoxCollider* other) {
    if(other->collisionLayer == 3) health--;
    if(health <= 0) markDestroyed();
}
