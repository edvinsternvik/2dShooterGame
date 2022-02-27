#include "Player.h"
#include "Input.h"
#include "Game.h"
#include "Bullet.h"

Player::Player() 
    : dir(0.0), boxCollider(std::make_shared<BoxCollider>(true)), m_bulletSprite(std::make_shared<Sprite>("assets/sprites/bullet.png")), m_bulletCooldown(0) {

    boxCollider->collisionLayer = 1;
    Game::collisionManager.registerCollider(boxCollider);
}

void Player::update(float deltaTime) {
    float speed = 8.0;
    if(Input::KeyDown(Key::KEY_W)) pos.y += speed * deltaTime;
    if(Input::KeyDown(Key::KEY_S)) pos.y -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_A)) pos.x -= speed * deltaTime;
    if(Input::KeyDown(Key::KEY_D)) pos.x += speed * deltaTime;

    if(pos.x < 0) pos.x = 0;
    if(pos.x > 19) pos.x = 19;
    if(pos.y < 0) pos.y = 0;
    if(pos.y > 10.25) pos.y = 10.25;

    glm::vec2 cursorPos = Input::GetCursorPos();
    glm::vec2 cursorPosWorldSpace = glm::vec2(cursorPos.x, 1.0 - cursorPos.y) * glm::vec2(320 / 16.0, 180 / 16.0);
    glm::vec2 cursorDir = glm::normalize(cursorPosWorldSpace - (pos + glm::vec2(0.5, 0.5)));

    if(m_bulletCooldown > 0) m_bulletCooldown -= deltaTime;
    if(Input::KeyDown(Key::KEY_SPACE) && m_bulletCooldown <= 0.0) {
        m_bulletCooldown = 0.05;

        Bullet* bullet = Game::entityManager.getEntity<Bullet>(Game::entityManager.create<Bullet>());
        bullet->setSprite(m_bulletSprite);
        bullet->pos = pos + glm::vec2(0.375, 0.375) + 0.75f * cursorDir;
        bullet->dir = glm::atan(cursorDir.y, cursorDir.x);
    }
    boxCollider->updatePos(pos, glm::vec2(1.0, 1.0));
}
