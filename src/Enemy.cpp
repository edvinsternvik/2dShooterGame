#include "Enemy.h"
#include "Game.h"
#include "Bullet.h"
#include "ParticleEmiiter.h"
#include "AnimatedSprite.h"

enum class EnemyAnimationStates : unsigned int {
    RunForward, RunRight, RunBack, RunLeft
};

Enemy::Enemy()
    : m_bulletCooldown(0.0), m_targetEntity(0), boxCollider(std::make_shared<BoxCollider>(false)), m_bulletSprite(std::make_shared<Sprite>("assets/sprites/bullet.png")) {
    
    boxCollider->collisionLayer = 2;
    boxCollider->setCollisionCallback(std::bind(&Enemy::collisionCallback, this, std::placeholders::_1));
    Game::collisionManager.registerCollider(boxCollider);
    health = 20;

    std::shared_ptr<Sprite> enemySprite = std::make_shared<AnimatedSprite>("assets/sprites/zombieSpritesheet.png", 4, 4, std::vector<AnimationData>{
        AnimationData(0, 0, {0.3, 0.3, 0.3, 0.3}), // Run forward
        AnimationData(0, 1, {0.3, 0.3, 0.3, 0.3}), // Run right
        AnimationData(0, 2, {0.3, 0.3, 0.3, 0.3}), // Run back
        AnimationData(0, 3, {0.3, 0.3, 0.3, 0.3})  // Run left
    });
    setSprite(enemySprite);
}

void Enemy::update(float deltaTime) {
    AnimatedSprite* sprite = dynamic_cast<AnimatedSprite*>(getSprite());

    Entity* target = Game::entityManager.getEntity(m_targetEntity);
    if(target != nullptr) {
        glm::vec2 dirToPlayer = glm::normalize(target->getPos() - getPos());
        if(std::abs(dirToPlayer.x) > std::abs(dirToPlayer.y)) {
            if(dirToPlayer.x > 0) sprite->setAnimationState(static_cast<unsigned int>(EnemyAnimationStates::RunRight));
            else                  sprite->setAnimationState(static_cast<unsigned int>(EnemyAnimationStates::RunLeft));
        }
        else {
            if(dirToPlayer.y > 0) sprite->setAnimationState(static_cast<unsigned int>(EnemyAnimationStates::RunBack));
            else                  sprite->setAnimationState(static_cast<unsigned int>(EnemyAnimationStates::RunForward));
        }

        glm::vec2 targetPos = target->getPos() - dirToPlayer * 0.6f;
        glm::vec2 targetDir = glm::normalize(targetPos - getPos());
        setPos(getPos() + targetDir * deltaTime);

        if(m_bulletCooldown > 0.0) m_bulletCooldown -= deltaTime;
        else {
            Bullet* bullet = Game::entityManager.getEntity<Bullet>(Game::entityManager.create<Bullet>());

            bullet->setSprite(m_bulletSprite);
            bullet->setPos(getPos() + dirToPlayer);
            bullet->dir = glm::atan(dirToPlayer.y, dirToPlayer.x);
            bullet->speed = 8.0f;
            bullet->boxCollider->collisionLayer = 4;

            m_bulletCooldown = 0.5;
        }

    }

    dynamic_cast<AnimatedSprite*>(getSprite())->updateAnimationFrame(deltaTime);
}

void Enemy::setPos(glm::vec2 newPos) {
    Entity::setPos(newPos);
    boxCollider->updatePos(newPos, glm::vec2(0.9, 0.4));
}

void Enemy::setTarget(entityID target) {
    m_targetEntity = target;
}

void Enemy::collisionCallback(BoxCollider* other) {
    if(other->collisionLayer == 3) { // Bullets
        health--;
        if(health <= 0) {
            entityID particleEmitter = Game::entityManager.create<ParticleEmitter>(glm::uvec2(50, 200), glm::vec2(3.0, 5.0), glm::vec2(2.0, 5.0), glm::vec2(0.0, glm::radians(360.0f)), glm::vec2(2.0, 5.0), glm::vec2(0.0, 0.8), glm::vec2(0.4, 0.6));
            Game::entityManager.getEntity(particleEmitter)->setPos(getPos() + glm::vec2(0.5, 0.5));
            Game::camera.cameraShakeIntensity = std::max(Game::camera.cameraShakeIntensity, 0.025f);

            markDestroyed();
        }

        Game::camera.cameraShakeIntensity = std::max(Game::camera.cameraShakeIntensity, 0.01f);
        entityID particleEmitter = Game::entityManager.create<ParticleEmitter>(glm::uvec2(10, 50), glm::vec2(1.0, 3.0), glm::vec2(2.0, 5.0), glm::vec2(0.0, glm::radians(360.0f)), glm::vec2(1.0, 2.0), glm::vec2(0.0, 0.25), glm::vec2(0.4, 0.6));
        Game::entityManager.getEntity(particleEmitter)->setPos(getPos() + glm::vec2(0.5, 0.5));
    }
}
