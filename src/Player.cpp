#include "Player.h"
#include "Input.h"
#include "Game.h"
#include "Bullet.h"
#include "AnimatedSprite.h"

enum class PlayerAnimationStates : unsigned int {
    IdleForward = 0, IdleRight, IdleBack, IdleLeft,
    RunForward,      RunRight,  RunBack,  RunLeft
};

Player::Player() 
    : dir(0.0), boxCollider(std::make_shared<BoxCollider>(true)), m_bulletSprite(std::make_shared<Sprite>("assets/sprites/bullet.png")), m_bulletCooldown(0), m_cameraShakeIntensity(0.0), m_timer(0.0) {

    std::shared_ptr<Sprite> playerSprite = std::make_shared<AnimatedSprite>("assets/sprites/PlayerSpritesheet.png", 8, 8, std::vector<AnimationData>{
        AnimationData(0, 0, {2.0, 0.1, 0.1, 0.1}), // Idle forward
        AnimationData(0, 1, {2.0, 0.1, 0.1, 0.1}), // Idle right
        AnimationData(0, 2, {2.0, 0.1, 0.1, 0.1}), // Idle back
        AnimationData(0, 3, {2.0, 0.1, 0.1, 0.1}), // Idle left
        AnimationData(4, 0, {0.1, 0.1, 0.1, 0.1}), // Run forward
        AnimationData(4, 1, {0.1, 0.1, 0.1, 0.1}), // Run right
        AnimationData(4, 2, {0.1, 0.1, 0.1, 0.1}), // Run back
        AnimationData(4, 3, {0.1, 0.1, 0.1, 0.1}) // Run left
    });
    setSprite(playerSprite);

    boxCollider->collisionLayer = 1;
    boxCollider->setCollisionCallback(std::bind(&Player::collisionCallback, this, std::placeholders::_1));
    Game::collisionManager.registerCollider(boxCollider);
}

void Player::update(float deltaTime) {
    AnimatedSprite* sprite = dynamic_cast<AnimatedSprite*>(getSprite());

    float speed = 8.0;
    glm::vec2 movement(0.0);
    if(Input::KeyDown(Key::KEY_W)) movement.y += speed * deltaTime;
    if(Input::KeyDown(Key::KEY_S)) movement.y -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_A)) movement.x -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_D)) movement.x += speed * deltaTime;

    glm::vec2 newPos = getPos() + movement;
    if(newPos.x < 0) newPos.x = 0;
    if(newPos.x > 19) newPos.x = 19;
    if(newPos.y < 0) newPos.y = 0;
    if(newPos.y > 10.25) newPos.y = 10.25;
    setPos(newPos);

    glm::vec2 cursorPos = Input::GetCursorPos();
    glm::vec2 cursorPosWorldSpace = glm::vec2(cursorPos.x, 1.0 - cursorPos.y) * glm::vec2(320 / 16.0, 180 / 16.0);
    glm::vec2 cursorDir = glm::normalize(cursorPosWorldSpace - (getPos() + glm::vec2(0.5, 0.5)));

    if(movement.x == 0.0 && movement.y == 0.0) {
        if(std::abs(cursorDir.x) > std::abs(cursorDir.y)) {
            if(cursorDir.x > 0) sprite->setAnimationState(static_cast<unsigned int>(PlayerAnimationStates::IdleRight));
            else                sprite->setAnimationState(static_cast<unsigned int>(PlayerAnimationStates::IdleLeft));
        }
        else {
            if(cursorDir.y > 0) sprite->setAnimationState(static_cast<unsigned int>(PlayerAnimationStates::IdleBack));
            else                sprite->setAnimationState(static_cast<unsigned int>(PlayerAnimationStates::IdleForward));
        }
    }
    else {
        if(std::abs(cursorDir.x) > std::abs(cursorDir.y)) {
            if(cursorDir.x > 0) sprite->setAnimationState(static_cast<unsigned int>(PlayerAnimationStates::RunRight));
            else                sprite->setAnimationState(static_cast<unsigned int>(PlayerAnimationStates::RunLeft));
        }
        else {
            if(cursorDir.y > 0) sprite->setAnimationState(static_cast<unsigned int>(PlayerAnimationStates::RunBack));
            else                sprite->setAnimationState(static_cast<unsigned int>(PlayerAnimationStates::RunForward));
        }
    }

    if(m_bulletCooldown > 0) m_bulletCooldown -= deltaTime;
    if(Input::KeyDown(Key::KEY_SPACE) && m_bulletCooldown <= 0.0) {
        m_bulletCooldown = 0.05;

        Bullet* bullet = Game::entityManager.getEntity<Bullet>(Game::entityManager.create<Bullet>());
        bullet->setSprite(m_bulletSprite);
        bullet->setPos(getPos() + glm::vec2(0.375, 0.25) + 0.5f * cursorDir);
        bullet->dir = glm::atan(cursorDir.y, cursorDir.x);
        bullet->speed = 12.0;
        bullet->boxCollider->collisionLayer = 3;
    }

    dynamic_cast<AnimatedSprite*>(getSprite())->updateAnimationFrame(deltaTime);

    m_timer += deltaTime;
    Game::cameraPos.x = m_cameraShakeIntensity * glm::sin(m_timer);
    Game::cameraPos.y = m_cameraShakeIntensity * glm::sin(m_timer + 100.0);
    m_cameraShakeIntensity = std::max(0.0f, m_cameraShakeIntensity - deltaTime);
}

void Player::setPos(glm::vec2 newPos) {
    Entity::setPos(newPos);
    boxCollider->updatePos(getPos(), glm::vec2(0.8, 0.3));
}

void Player::collisionCallback(BoxCollider* other) {
    m_cameraShakeIntensity = 0.01;
}
