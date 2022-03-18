#include "Enemy.h"
#include "Game.h"
#include "Bullet.h"
#include "ParticleEmiiter.h"

Enemy::Enemy()
    : m_bulletCooldown(0.0), m_targetEntity(0), boxCollider(std::make_shared<BoxCollider>(false)), m_bulletSprite(std::make_shared<Sprite>("assets/sprites/bullet.png")) {
    
    boxCollider->collisionLayer = 2;
    boxCollider->setCollisionCallback(std::bind(&Enemy::collisionCallback, this, std::placeholders::_1));
    Game::collisionManager.registerCollider(boxCollider);
    health = 20;
}

void Enemy::update(float deltaTime) {
    if(m_bulletCooldown > 0.0) m_bulletCooldown -= deltaTime;
    else {
        Entity* target = Game::entityManager.getEntity(m_targetEntity);
        if(target != nullptr) {
            Bullet* bullet = Game::entityManager.getEntity<Bullet>(Game::entityManager.create<Bullet>());

            glm::vec2 dirToPlayer = glm::normalize(target->getPos() - getPos());
            bullet->setSprite(m_bulletSprite);
            bullet->setPos(getPos() + dirToPlayer);
            bullet->dir = glm::atan(dirToPlayer.y, dirToPlayer.x);
            bullet->speed = 8.0f;
            bullet->boxCollider->collisionLayer = 4;

            m_bulletCooldown = 0.5;
        }
    }
}

void Enemy::setPos(glm::vec2 newPos) {
    Entity::setPos(newPos);
    boxCollider->updatePos(newPos, glm::vec2(0.9, 0.4));
}

void Enemy::setTarget(entityID target) {
    m_targetEntity = target;
}

void Enemy::collisionCallback(BoxCollider* other) {
    if(other->collisionLayer == 3) {
        health--;
        if(health <= 0) {
            entityID particleEmitter = Game::entityManager.create<ParticleEmitter>(glm::uvec2(50, 200), glm::vec2(3.0, 5.0), glm::vec2(2.0, 5.0), glm::vec2(0.0, glm::radians(360.0f)), glm::vec2(2.0, 5.0), glm::vec2(0.0, 0.8), glm::vec2(0.4, 0.6));
            Game::entityManager.getEntity(particleEmitter)->setPos(getPos() + glm::vec2(0.5, 0.5));

            markDestroyed();
        }

        Game::camera.cameraShakeIntensity = std::max(Game::camera.cameraShakeIntensity, 0.01f);
        entityID particleEmitter = Game::entityManager.create<ParticleEmitter>(glm::uvec2(10, 50), glm::vec2(1.0, 3.0), glm::vec2(2.0, 5.0), glm::vec2(0.0, glm::radians(360.0f)), glm::vec2(1.0, 2.0), glm::vec2(0.0, 0.25), glm::vec2(0.4, 0.6));
        Game::entityManager.getEntity(particleEmitter)->setPos(getPos() + glm::vec2(0.5, 0.5));
    }
}
