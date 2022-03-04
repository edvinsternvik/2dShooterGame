#include "Player.h"
#include "Input.h"
#include "Game.h"
#include "Bullet.h"

Player::Player() 
    : dir(0.0), boxCollider(std::make_shared<BoxCollider>(true)), m_bulletSprite(std::make_shared<Sprite>("assets/sprites/bullet.png")), m_bulletCooldown(0), m_cameraShakeIntensity(0.0), m_timer(0.0) {

    boxCollider->collisionLayer = 1;
    boxCollider->setCollisionCallback(std::bind(&Player::collisionCallback, this, std::placeholders::_1));
    Game::collisionManager.registerCollider(boxCollider);
}

void Player::update(float deltaTime) {
    float speed = 8.0;
    glm::vec2 newPos = getPos();
    if(Input::KeyDown(Key::KEY_W)) newPos.y += speed * deltaTime;
    if(Input::KeyDown(Key::KEY_S)) newPos.y -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_A)) newPos.x -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_D)) newPos.x += speed * deltaTime;

    if(newPos.x < 0) newPos.x = 0;
    if(newPos.x > 19) newPos.x = 19;
    if(newPos.y < 0) newPos.y = 0;
    if(newPos.y > 10.25) newPos.y = 10.25;
    setPos(newPos);

    glm::vec2 cursorPos = Input::GetCursorPos();
    glm::vec2 cursorPosWorldSpace = glm::vec2(cursorPos.x, 1.0 - cursorPos.y) * glm::vec2(320 / 16.0, 180 / 16.0);
    glm::vec2 cursorDir = glm::normalize(cursorPosWorldSpace - (getPos() + glm::vec2(0.5, 0.5)));

    if(m_bulletCooldown > 0) m_bulletCooldown -= deltaTime;
    if(Input::KeyDown(Key::KEY_SPACE) && m_bulletCooldown <= 0.0) {
        m_bulletCooldown = 0.05;

        Bullet* bullet = Game::entityManager.getEntity<Bullet>(Game::entityManager.create<Bullet>());
        bullet->setSprite(m_bulletSprite);
        bullet->setPos(getPos() + glm::vec2(0.375, 0.375) + 0.75f * cursorDir);
        bullet->dir = glm::atan(cursorDir.y, cursorDir.x);
        bullet->speed = 12.0;
        bullet->boxCollider->collisionLayer = 3;
    }

    m_timer += deltaTime;
    Game::cameraPos.x = m_cameraShakeIntensity * glm::sin(m_timer * 100.0);
    Game::cameraPos.y = m_cameraShakeIntensity * glm::sin(m_timer * 100.0 + 100.0);
    m_cameraShakeIntensity = std::max(0.0f, m_cameraShakeIntensity - deltaTime);
}

void Player::setPos(glm::vec2 newPos) {
    Entity::setPos(newPos);
    boxCollider->updatePos(getPos(), glm::vec2(0.8, 0.3));
}

void Player::collisionCallback(BoxCollider* other) {
    m_cameraShakeIntensity = 0.01;
}
